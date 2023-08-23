// Esqueleto(c) Realidad Virtual y Aumentada - Universidad de Cordoba - Manuel J. Marin-Jimenez

// Includes necesarios
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/features2d.hpp" 
#include "opencv2/xfeatures2d.hpp"
#include <opencv2/imgproc/imgproc.hpp>

#include "rva.h"

//cmake para compilar opencv con los modulos NONFREE
//cmake -D CMAKE_BUILD_TYPE=RELEASE -D OPENCV_ENABLE_NONFREE=ON -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules -D WITH_GTK=ON -D CMAKE_INSTALL_PREFIX=/usr/local -DFORCE_VTK=ON -DWITH_TBB=ON -DWITH_V4L=ON -DWITH_QT=ON -DWITH_OPENGL=ON -DWITH_CUBLAS=ON -DCUDA_NVCC_FLAGS="-D_FORCE_INLINES" -DWITH_GDAL=ON -DWITH_XINE=ON -DBUILD_EXAMPLES=ON ..


// ====================================
// Functions for task 1
// ====================================
cv::Mat rva_compute_homography(std::vector<cv::Point2f> points_image1, std::vector<cv::Point2f> points_image2){
    return cv::findHomography(points_image1, points_image2,cv::RANSAC);//usar cv::RANSAC
}

void rva_draw_contour(cv::Mat image, std::vector<cv::Point2f> points, cv::Scalar color, int thickness){
    cv::line(image, points[0], points[1], color, thickness);//se puede hacer con un bucle for
    cv::line(image, points[1], points[2], color, thickness);
    cv::line(image, points[2], points[3], color, thickness);
    cv::line(image, points[3], points[0], color, thickness);
}

void rva_deform_image(const cv::Mat& im_input, cv::Mat & im_output, cv::Mat homography){
    cv::warpPerspective(im_input, im_output, homography, im_output.size());
}


// ====================================
// Functions for task 2
// ====================================
void rva_calculaKPsDesc(const cv::Mat &img, std::vector<cv::KeyPoint> &keypoints, cv::Mat &descriptors, bool tipo_kp_float)
{
    if (!tipo_kp_float){
        auto Detector=cv::AKAZE::create(cv::AKAZE::DESCRIPTOR_MLDB,  0,  3, 1e-4f,8 );
        Detector ->detectAndCompute(img, cv::Mat(), keypoints, descriptors);
    }else{
        //cv::Mat tmp;
        //cv::cvtColor(img, tmp, cv::COLOR_BGR2GRAY );
        auto Detector=cv::xfeatures2d::SURF::create(400);
        Detector->detectAndCompute(img, cv::noArray(), keypoints, descriptors);
    }
}

void rva_matchDesc(const cv::Mat &descriptors1, const cv::Mat &descriptors2, std::vector<cv::DMatch> &matches, bool tipo_kp_float)
{ 
    std::vector< std::vector<cv::DMatch> > knn_matches;
    if(!tipo_kp_float){
        auto matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");
        matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);
    }else{
        auto matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
        matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);
    }

    //si se quieren aplicar filtros debe ser aqui
    //-- Filter matches using the Lowe's ratio test
    const float ratio_thresh = 0.75f;
    std::vector<cv::DMatch> good_matches;
    for (size_t i = 0; i < knn_matches.size(); i++)
    {
        if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
        {
            good_matches.push_back(knn_matches[i][0]);
        }
    }
    matches = good_matches;
}

void rva_dibujaMatches(cv::Mat &img1, cv::Mat &img2, std::vector<cv::KeyPoint> &keypoints1, std::vector<cv::KeyPoint> &keypoints2, std::vector<cv::DMatch> &matches, cv::Mat &img_matches)
{
    cv::drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);
}

// ====================================
// Functions for task 3
// ====================================
void rva_localizaObj(const cv::Mat &img1, const cv::Mat &img2, const std::vector<cv::KeyPoint> &keypoints1, const std::vector<cv::KeyPoint> &keypoints2, const std::vector<cv::DMatch> &matches, cv::Mat &homography, std::vector<cv::Point2f> &pts_im2)
{
    //-- Para hacer la homografia necesitamos pasarle a la funcion los matches encontrados(los keypoint)
    std::vector<cv::Point2f> obj;
    std::vector<cv::Point2f> scene;
    for( size_t i = 0; i < matches.size(); i++ )
    {
        //-- Get the keypoints from the good matches
        obj.push_back( keypoints1[ matches[i].queryIdx ].pt );
        scene.push_back( keypoints2[ matches[i].trainIdx ].pt );
    }
    //calculamos la homografia
    homography = rva_compute_homography(obj, scene);

    //Guardamos las coordenadas de las esquinas de la imagen patron
    std::vector<cv::Point2f> patron_corners(4);
    patron_corners[0] = cv::Point2f(0, 0);
    patron_corners[1] = cv::Point2f( (float)img1.cols, 0 );
    patron_corners[2] = cv::Point2f( (float)img1.cols, (float)img1.rows );
    patron_corners[3] = cv::Point2f( 0, (float)img1.rows );

    //Calculamos las esquinas en la imagen con la homografía
    perspectiveTransform(patron_corners, pts_im2, homography);
}

// ====================================
// Functions for task 4
// ====================================
void rva_dibujaPatch_sin_calib(const cv::Mat & scene, const cv::Mat & patch, const cv::Mat & H, cv::Mat & output, const std::vector<cv::Point2f>& pts_obj_in_scene)
{

    //version sin calibracion
    cv::Mat imgtmp(scene.rows,scene.cols,scene.type());
    rva_deform_image(patch, imgtmp, H);
    //cv::bitwise_and(scene,imgtmp,output);
    //necesario definir el cuadrado de la escena a eliminar, sino da problemas
    std::vector<cv::Point> img_points_int;//necesito coger las esquinas en perspectiva
    for(int i = 0; i < pts_obj_in_scene.size(); i++){
        img_points_int.push_back(cv::Point((int)pts_obj_in_scene[i].x,(int)pts_obj_in_scene[i].y)); 
    }
    cv::fillConvexPoly(output,img_points_int,cv::Scalar(0,0,0));
    output=output|imgtmp;
}

// ====================================
// Funciones de apoyo creadas por mí
// ====================================
void fsiv_load_calibration_parameters(cv::FileStorage &fs,
                                 cv::Mat& camera_matrix,
                                 cv::Mat& dist_coeffs,
                                 cv::Mat& rvec,
                                 cv::Mat& tvec)
{
    fs["camera-matrix"] >> camera_matrix;
    fs["distortion-coefficients"] >> dist_coeffs;
    fs["rvec"] >> rvec;
    fs["tvec"] >> tvec;

    return;
}

std::vector<cv::Point3f> fsiv_generate_3d_calibration_points(int ancho,
                                    int largo)
{
    std::vector<cv::Point3f> v_puntos3d;
    v_puntos3d.push_back(cv::Point3f(0, 0, 0));
    v_puntos3d.push_back(cv::Point3f(float(ancho), 0, 0));
    v_puntos3d.push_back(cv::Point3f(float(ancho), float(largo), 0));
    v_puntos3d.push_back(cv::Point3f(0, float(largo), 0));
    return v_puntos3d;
}

void rva_dibujaPatch_con_calib(const cv::Mat & scene, const cv::Mat & patch, const cv::Mat & H, cv::Mat & output, const std::vector<cv::Point2f>& _2dpoints)
{
    //esquinas de la imagen a introducir
    std::vector<cv::Point2f> dst_p;
    dst_p.clear();
    dst_p.push_back(cv::Point2f(0, 0));
    dst_p.push_back(cv::Point2f(0, patch.rows));
    dst_p.push_back(cv::Point2f(patch.cols, patch.rows));
    dst_p.push_back(cv::Point2f(patch.cols, 0));

    cv::Mat aux;
    //calculamos la matrix que perminte transformar los puntos calculados (2d coordenada base) a la escena (3d a 2d)
    cv::Mat matriz_trans=cv::getPerspectiveTransform(dst_p, _2dpoints);
    //cambio patch a perspectiva de la escena con el tamaño de la misma
    cv::warpPerspective(patch, aux, matriz_trans, cv::Size(scene.cols,scene.rows));

    std::vector<cv::Point> img_points_int;//necesito coger las esquinas en perspectiva
    for(int i = 0; i < _2dpoints.size(); i++){
        img_points_int.push_back(cv::Point((int)_2dpoints[i].x,(int)_2dpoints[i].y)); 
    }
    //recortamos en la escena el lugar donde va la imagen y las fusionamos en la salida
    cv::fillConvexPoly(scene,img_points_int,cv::Scalar(0,0,0));
    output=scene|aux;
}

void rva_dibujaCasita_con_calib(cv::Mat & img_scene, 
                                 const cv::Mat& camera_matrix,
                                 const cv::Mat& dist_coeffs,
                                 const cv::Mat& rvec,
                                 const cv::Mat& tvec, 
                                 std::vector<cv::Point2f>& _2dpoints){

    //Marcamos los puntos con los que vamos a trabajar

    //Puntos para representar el eje de coordenadas
    std::vector<cv::Point3f> ejes;
    ejes.push_back(cv::Point3f(0,0,0));
    ejes.push_back(cv::Point3f(2,0,0));
    ejes.push_back(cv::Point3f(0,2,0));
    ejes.push_back(cv::Point3f(0,0,(-2)));

    //proyectamos los puntos para la pose de la camara
    projectPoints(ejes, rvec, tvec, camera_matrix, dist_coeffs, _2dpoints);

    //pintamos las coordenadas del eje
    cv::line(img_scene, _2dpoints[0], _2dpoints[1], cv::Scalar(0,0,255), 2);
    cv::line(img_scene, _2dpoints[0], _2dpoints[2], cv::Scalar(255,255,0), 2);
    cv::line(img_scene, _2dpoints[0], _2dpoints[3], cv::Scalar(255,0,0), 2);

    //dibujo de la casa
    std::vector<cv::Point3f> casa;
    //coordenadas importantes paredes
    casa.push_back(cv::Point3f(10,10,0));
    casa.push_back(cv::Point3f(15,10,0));
    casa.push_back(cv::Point3f(10,15,0));
    casa.push_back(cv::Point3f(15,15,0));
    casa.push_back(cv::Point3f(10,10,-10));
    casa.push_back(cv::Point3f(15,10,-10));
    casa.push_back(cv::Point3f(10,15,-10));
    casa.push_back(cv::Point3f(15,15,-10));
    //coordenas importantes techo
    casa.push_back(cv::Point3f(13,13,-15));

    //puntos para dibujar la camara
    projectPoints(casa, rvec, tvec, camera_matrix, dist_coeffs, _2dpoints);

    //dibujo lineas para mayor claridad
    //para las paredes
    cv::line(img_scene, _2dpoints[0], _2dpoints[4], cv::Scalar(0,0,0), 5);
    cv::line(img_scene, _2dpoints[1], _2dpoints[5], cv::Scalar(0,0,0), 5);
    cv::line(img_scene, _2dpoints[2], _2dpoints[6], cv::Scalar(0,0,0), 5);
    cv::line(img_scene, _2dpoints[3], _2dpoints[7], cv::Scalar(0,0,0), 5);

    std::vector<cv::Point> tmp;

    //pinto paredes
    cv::fillConvexPoly(img_scene, tmp = {_2dpoints[0], _2dpoints[1], _2dpoints[5], _2dpoints[4]}, cv::Scalar(0,255,255), cv::LINE_AA, 0);
    cv::fillConvexPoly(img_scene, tmp = {_2dpoints[0], _2dpoints[2], _2dpoints[6], _2dpoints[4]}, cv::Scalar(0,255,255), cv::LINE_AA, 0);
    cv::fillConvexPoly(img_scene, tmp = {_2dpoints[3], _2dpoints[1], _2dpoints[5], _2dpoints[7]}, cv::Scalar(0,255,255), cv::LINE_AA, 0);
    cv::fillConvexPoly(img_scene, tmp = {_2dpoints[3], _2dpoints[2], _2dpoints[6], _2dpoints[7]}, cv::Scalar(0,255,255), cv::LINE_AA, 0);

    //pinto tejado
    cv::fillPoly(img_scene, tmp = {_2dpoints[5], _2dpoints[4], _2dpoints[8]}, cv::Scalar(0, 0, 255));
    cv::fillPoly(img_scene, tmp = {_2dpoints[5], _2dpoints[7], _2dpoints[8]}, cv::Scalar(0, 0, 255));
    cv::fillPoly(img_scene, tmp = {_2dpoints[6], _2dpoints[7], _2dpoints[8]}, cv::Scalar(0, 0, 255));
    cv::fillPoly(img_scene, tmp = {_2dpoints[6], _2dpoints[4], _2dpoints[8]}, cv::Scalar(0, 0, 255));

    //para el techo perfilo
    cv::line(img_scene, _2dpoints[4], _2dpoints[5], cv::Scalar(0,0,0), 2);
    cv::line(img_scene, _2dpoints[5], _2dpoints[7], cv::Scalar(0,0,0), 2);
    cv::line(img_scene, _2dpoints[7], _2dpoints[6], cv::Scalar(0,0,0), 2);
    cv::line(img_scene, _2dpoints[6], _2dpoints[4], cv::Scalar(0,0,0), 2);

    cv::line(img_scene, _2dpoints[4], _2dpoints[8], cv::Scalar(0,0,0), 2);
    cv::line(img_scene, _2dpoints[5], _2dpoints[8], cv::Scalar(0,0,0), 2);
    cv::line(img_scene, _2dpoints[6], _2dpoints[8], cv::Scalar(0,0,0), 2);
    cv::line(img_scene, _2dpoints[7], _2dpoints[8], cv::Scalar(0,0,0), 2);
}