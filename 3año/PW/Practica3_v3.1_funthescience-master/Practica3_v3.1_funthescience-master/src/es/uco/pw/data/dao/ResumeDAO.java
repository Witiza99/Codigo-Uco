package es.uco.pw.data.dao;

import es.uco.pw.display.bean.ResumeBean;
import es.uco.pw.utilities.CreatePDF;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Properties;


public class ResumeDAO extends ConexionDAO{
	
	private ResumeBean cvBean;
	
	/**
	 * 
	 * @brief constructor que recibe como parametro objeto Properties
	 * @param properties contiene los valores para establece conexion a la base de datos
	 */
	public ResumeDAO(Properties properties) {
		super(properties);
	}

	/**
	 * 
	 * @param lista array String que contiene los valores de varias columnas de la base de datos
	 * @param languages array de valores del checkbox languages de cvResumeView
	 * @param programming array de valores del checkbox programming de cvResumeView
	 * @param aceptar array que determina si el usuario aceptar mostrar el CV
	 * @return boolean
	 */
	@SuppressWarnings("resource")
	public boolean cvUser(String [] lista,String [] languages,String[]programming,int show_cv) {
		conexion();
		try {
			
			Connection con = getConnect();
			
			PreparedStatement ps;
			
			int id = Integer.parseInt(lista[8]);
			
			ps = con.prepareStatement("select * from cv_resume where id_user = ?");
			ps.setInt(1,id);
			
			ResultSet rs = ps.executeQuery();
			
			int status = 0;
			//convertimos el checkbox en un String con sus valores
			String program = valuesList(programming);
			//convertimos el checkbox en un String con sus valores
			String lang = valuesList(languages);
			int phone = Integer.parseInt(lista[4]);
			String mensaje = "";
			
			String update = "update cv_resume set fullName = ?,brief_intro=?,address=?,email=?,phone=?,experience_professional=?,languages=?"
					+ ",programming=?,studies=?,referer=?,showCV=? where id = ? ";
			
			String insert = "Insert into cv_resume(id,fullName,brief_intro,address,email,phone,experience_professional,languages,programming,studies,referer,showCV,id_user) values(NULL,?,?,?,?,?,?,?,?,?,?,?,?)";

			if(rs.next() == true) {//entonces se haria un update
				
				id = rs.getInt("id");
				ps = con.prepareStatement(update);
				mensaje = "Error al modificar los datos de Curriculum";
				
			}else {//entonces se hace un insert
				
				ps = con.prepareStatement(insert);
				mensaje = "Error al insertar los datos de Curriculum";
			}
			
			ps.setString(1,lista[0]);
			ps.setString(2,lista[1]);
			ps.setString(3,lista[2]);
			ps.setString(4,lista[3]);
			ps.setInt(5,phone);//
			ps.setString(6,lista[5]);
			ps.setString(7,lang);//languages
			ps.setString(8,program);//programming
			ps.setString(9,lista[6]);
			ps.setString(10,lista[7]);
			ps.setInt(11,show_cv);
			ps.setInt(12,id);

			
			status = ps.executeUpdate();
			
			if(status == 0) {
				System.out.println(mensaje);
				cerrarConexion();
				return false;
			}
			
		}catch(SQLException e){
			System.out.println(e);
			cerrarConexion();
			return false;
		}
		
		cerrarConexion();
		return true;
	}
	
	/**
	 * @param lista parametro que recibe un array de String y lo convierte en un Objeto String
	 * @brief convierte un array de String en una cadena de String
	 */
	private String valuesList(String [] lista) {
		String auxiliar = "";
		for(int i = 0;i < lista.length;i++) {
			auxiliar += lista[i];
			if(i+1 < lista.length) {
				auxiliar += ",";
			}
		}
		return auxiliar;
	}
	
	/* creacion de pdf */
	/**
	 * 
	 * @brief metodo que creara archivo PDF a partir de una consulta a base de datos
	 * @param index indica el atributo indice del autor
	 * @param path indica el lugar donde se guardara el pdf del CV del autor, si esta vacio no se generara
	 * @return boolean
	 */
	public boolean dataForPDF(int index,String path) {
		conexion();
		try {
			Connection con = getConnect();
			PreparedStatement ps = con.prepareStatement("select * from cv_resume where id_user = ?");
			ps.setInt(1,index);
			
			ResultSet rs = ps.executeQuery();
			
			if(rs.next() == false) {
				System.out.println("No se ha hallado datos segun el indice de la consulta");
				cerrarConexion();
				return false;
			}
			
			rs.beforeFirst();
			rs.next();
			
			cvBean = new ResumeBean();

			cvBean.setFullName(rs.getString("fullName"));
			cvBean.setBrief_intro(rs.getString("brief_intro"));
			cvBean.setAddress(rs.getString("address"));
			cvBean.setEmail(rs.getString("email"));
			cvBean.setPhone(rs.getInt("phone"));
			cvBean.setExperience_professional(rs.getString("experience_professional"));
			cvBean.setLanguages(rs.getString("languages"));
			cvBean.setProgramming(rs.getString("programming"));
			cvBean.setStudies(rs.getString("studies"));
			cvBean.setReferer(rs.getString("referer"));
			cvBean.setShow_cv(rs.getInt("showCV"));
			
			if(!path.equals("")) {
				createPDFDao(cvBean,path);
			}
			
		}catch(SQLException e){
			System.out.println(e);
			cerrarConexion();
			return false;
		}
		
		cerrarConexion();
		return true;
	}
	
	/**
	 * 
	 * @brief devuelve objeto de la clase ResumeBean
	 * @return objeto de ResumeBean
	 */
	public ResumeBean getCVResume() {
		return cvBean;
	}
	
	/**
	 * 
	 * @brief creara el PDF del CV del autor
	 * @param resume objeto de ResumeBean con los datos a guardar en PDF
	 * @param path lugar donde se guardara el PDF
	 */
	public void createPDFDao(ResumeBean resume,String path) {
		String file = Integer.toString(resume.getPhone());
		file += ".pdf";
		path += file;
		 CreatePDF create = new CreatePDF(path,resume);
		 create.generatePDF();
	}
	
	/**
	 * 
	 * @brief metodo para obtener el valor phone del autor de proyecto y carga de su pdf.
	 * @param index indice del autor del proyecto.
	 * @return entero
	 */
	public int[] getPhoneCV(int index) {
		conexion();
		int number[] = {0,0};
		try {
			Connection con = getConnect();
			PreparedStatement ps = con.prepareStatement("select phone,showCV from cv_resume where id_user = ?");
			ps.setInt(1,index);
			
			ResultSet rs = ps.executeQuery();
			
			if(rs.next() == false) {
				System.out.println("No se encontro la sentencia.");
				cerrarConexion();
				return number;
			}
			
			rs.beforeFirst();
			rs.next();
			
			number[0] = rs.getInt("phone");
			number[1] = rs.getInt("showCV");
			
		}catch(SQLException e) {
			System.out.println(e);
			cerrarConexion();
		}
		
		cerrarConexion();
		return number;
	}
	
	
	/**
	 * 
	 * @brief metodo que guardará el valor para mostrar cv de autor a publico o no. 
	 * @param valor define si se mostrara el CV del autor o no.
	 * @param index indice del autor
	 * @return boolean
	 */
	public boolean showCVUsers(int valor,int index) {
		conexion();
		
		try {
			Connection con = getConnect();
			PreparedStatement ps = con.prepareStatement("update cv_resume set showCV = ? where id_user = ?");
			ps.setInt(1,valor);
			ps.setInt(2,index);
			
			int status = ps.executeUpdate();
			
			if(status == 0) {
				System.out.println("Error al modificar los datos de Curriculum");
				cerrarConexion();
				return false;
			}
			
		}catch(SQLException e) {
			System.out.println(e);
			cerrarConexion();
		}
		
		cerrarConexion();
		return true;
	}
}