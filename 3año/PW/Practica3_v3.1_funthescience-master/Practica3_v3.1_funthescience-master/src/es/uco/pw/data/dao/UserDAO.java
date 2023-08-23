/**
 * 
 * Esta clase se utiliza para conectar la base de datos para el tratamiento de los datos de los usuarios
 * @author Oscar Godoy Calderon
 * @date 05-01-2020
 */

package es.uco.pw.data.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Properties;

import es.uco.pw.display.bean.CustomerBean;


public class UserDAO extends ConexionDAO{
	
	private CustomerBean customerBean;

	/**
	 * @brief constructor de la clase UserDAO
	 * @param properties
	 */
	public UserDAO(Properties properties) {
		super(properties);
	}
	
	/**
	 * 
	 * @brief devuelve un objeto de la clase CustomerBean
	 * @return CustomerBean
	 */
	public CustomerBean getCustomer() {
		return customerBean;
	}
	
	/**
	 * @brief se instancia a la propiedad customerBean un objeto de la misma clase
	 * @param cb
	 */
	public void setCustomer(CustomerBean cb) {
		customerBean=cb;
	}
	
	/**
	 * 
	 * @brief metodo para verificar los valores proporcionados por el formulario de login
	 * @param email valor email del usuario
	 * @param password valor del password del usuario
	 * @return boolean
	 */
	public boolean userLogin(String email,String password) {
		conexion();

		try {

			Connection con = getConnect();

			PreparedStatement ps =  con.prepareStatement("select * from login where correo = ? and password = ? ");

			ps.setString(1,email);
			ps.setString(2,password);
			
			ResultSet rs = ps.executeQuery();
			
			if(rs.next() == false) {
				cerrarConexion();
				return false;
			}
			
			rs.beforeFirst();
			rs.next();
			customerBean = new CustomerBean();
			
			customerBean.setIndex(rs.getInt("indice"));

			customerBean.setEmail(rs.getString("correo"));

			customerBean.setName((String)rs.getString("nombre"));

			customerBean.setLastName(rs.getString("apellidos"));

			customerBean.setPhone(rs.getInt("telefono"));

			customerBean.setAddress(rs.getString("direccion"));

			customerBean.setProvince(rs.getString("provincia"));

			customerBean.setLocation(rs.getString("localidad"));

			customerBean.setCountry(rs.getString("pais"));

			customerBean.setProfession(rs.getString("profesion"));

			customerBean.setDNI(rs.getString("dni"));

			customerBean.setPassword(rs.getString("password"));

			customerBean.setAdditional_paragraph(rs.getString("parrafo_adicional"));

		}catch(SQLException e) {
			System.out.println(e);
			cerrarConexion();
			return false;
		}
		cerrarConexion();
		
		return true;
	}
	
	public boolean register(CustomerBean cb) {
		conexion();
		try {
			Connection con = getConnect();
			
			PreparedStatement ps=con.prepareStatement("select * from login where correo=?");
			ps.setString(1,cb.getEmail()); 
			
			ResultSet rs = ps.executeQuery();
			
			if(rs.next() != false) {
				System.out.println("Ya existe un usuario con ese correo");
				cerrarConexion();
				return false;
			}
			
			ps=con.prepareStatement("insert into login values(NULL,?,?,?,?,?,?,?,?,?,?,?,?)");  
			ps.setString(1,cb.getEmail());  
			ps.setString(2,cb.getName());  
			ps.setString(3,cb.getLastName()); 
			ps.setInt(4,cb.getPhone()); 
			ps.setString(5,cb.getAddress()); 
			ps.setString(6,cb.getProvince()); 
			ps.setString(7,cb.getLocation()); 
			ps.setString(8,cb.getCountry()); 
			ps.setString(9,cb.getProfession()); 
			ps.setString(10,cb.getDNI()); 
			ps.setString(11,cb.getPassword()); 
			ps.setString(12,cb.getAdditional_paragraph()); 
			
			int status = ps.executeUpdate();
			
			if(status==0) {
				System.out.println("Error al introducir en la base de datos");
				cerrarConexion();
				return false;
			}
		}catch(SQLException e) {
			System.out.println(e);
			cerrarConexion();
			return false;
		}
		setCustomer(cb);
		cerrarConexion();
		return true;
	}
	
	/**
	 * 
	 * @brief metodo para obtener todos los datos del usuario para cagarlos en el perfil
	 * @param index indice del usuario
	 * @return boolean
	 */
	public boolean queryUserProfile(int index) {
		conexion();
		try {
			Connection con = getConnect();
			String id = Integer.toString(index);
			
			PreparedStatement ps = con.prepareStatement("select * from login where indice = ?");
			ps.setString(1,id);
			
			ResultSet rs = ps.executeQuery();
			
			if(rs.next() == false) {
				cerrarConexion();
				return false;
			}
			
			rs.beforeFirst();
			
			rs.next();
			
			customerBean = new CustomerBean();
			
			customerBean.setIndex(index);

			customerBean.setEmail(rs.getString("correo"));

			customerBean.setName((String)rs.getString("nombre"));

			customerBean.setLastName(rs.getString("apellidos"));

			customerBean.setPhone(rs.getInt("telefono"));

			customerBean.setAddress(rs.getString("direccion"));

			customerBean.setProvince(rs.getString("provincia"));

			customerBean.setCountry(rs.getString("pais"));

			customerBean.setProfession(rs.getString("profesion"));

			customerBean.setAdditional_paragraph(rs.getString("parrafo_adicional"));
			
		}catch(SQLException e) {
			System.out.println(e);
			return false;
		}
		
		cerrarConexion();
		return true;
	}

	
	/**
	 * 
	 * @brief metodo para actualizar los datos de perfil del usuario 
	 * @param lista array de lista de los valores del usuario que modifica
	 * @param index indice del usuario para modificar su tupla en la tabla
	 * @return boolean
	 */
	public boolean updateDataUser(String [] lista,int index) {
		conexion();
		try {
			Connection con = getConnect();
			
			int phone = Integer.parseInt(lista[3]);

			PreparedStatement ps =  con.prepareStatement("UPDATE login set correo=?,nombre=?,apellidos=?,telefono=?,direccion=?,provincia=?,localidad=?,pais=?,profesion=?,password=?,parrafo_adicional=? where indice = ?");
			ps.setString(1,lista[0]);
			ps.setString(2,lista[1]);
			ps.setString(3,lista[2]);
			ps.setInt(4,phone);
			ps.setString(5,lista[4]);
			ps.setString(6,lista[5]);
			ps.setString(7,lista[6]);
			ps.setString(8,lista[7]);
			ps.setString(9,lista[8]);
			ps.setString(10,lista[9]);
			ps.setString(11,lista[10]);
			ps.setInt(12,index);
			
			int status = ps.executeUpdate();
			
			if(status == 0) {
				System.out.println("Error al modificar los datos de perfil");
				cerrarConexion();
				return false;
			}
			
		}catch(SQLException e) {
			System.out.println(e);
			cerrarConexion();
			return false;
		}
		cerrarConexion();
		return true;
	}


}
