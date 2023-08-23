/**
 * 
 * Esta clase se utiliza para realizar las herencias a las subclases para la conexion a la base de datos
 * @author Oscar Godoy Calderon
 * @date 05-01-2020
 */

package es.uco.pw.data.dao;


import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Properties;

public class ConexionDAO {
	
	private Properties properties;
	
	private Connection connect;

	/**
	 * @brief constructor que recibe como parametros un objeto de la clase Properties
	 * @param properties
	 */
	public ConexionDAO(Properties properties) {
		this.properties = properties;
	}
	
	/**
	 * @brief funcion que establece la conexion a la base de datos
	 * @return tipo booleano
	 */
	public boolean conexion() {
		String driver = (String)properties.get("driver");
		String db = (String)properties.get("dbconn");
	    Properties auxiliar = new Properties();
	    auxiliar.put("user",(String)properties.get("user"));
	    auxiliar.put("password",(String)properties.get("password"));
		try {
	        Class.forName(driver);
	        //connect = DriverManager.getConnection((String)properties.get("dbconn"),(String)properties.get("user"),(String)properties.get("password"));
	        connect = DriverManager.getConnection(db,auxiliar);
		}catch(SQLException e) {
			System.out.println(e);
			return false;
		}catch(ClassNotFoundException e) {
			System.out.println(e);
			return false;
		}
		
		return true;
	}
	
	/**
	 * @brief cierra la conexion a la base de datos
	 * @return tipo booleano
	 */
	public boolean cerrarConexion(){
		try {
			connect.close();
		}catch(SQLException e) {
			System.out.println(e);
			return false;
		}
		return true;
	}
	
	/**
	 * @brief devuelve el objeto de Connection para cerrar realizar consultas o modificacion en la base de datos de las clases que hereden de ConexionDAO
	 * @return el objeto connect de la clase Connection
	 */
	public Connection getConnect() {
		return connect;
	}
	
}