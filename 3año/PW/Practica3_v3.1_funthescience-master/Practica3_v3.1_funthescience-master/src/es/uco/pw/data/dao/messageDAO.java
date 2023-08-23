package es.uco.pw.data.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Properties;

import es.uco.pw.display.bean.ProjectBean;
import es.uco.pw.display.bean.messageBean;

public class messageDAO extends ConexionDAO{

	public messageDAO(Properties properties) {
		super(properties);
	}
	
	//Obetener los mensajes por el id del proyecto
	public ArrayList<messageBean> getMessagesPID(String pid){
		ArrayList<messageBean> msgs = new ArrayList<messageBean>();
		conexion();
		
		try {
			
			Connection con = getConnect();		
			PreparedStatement ps =  con.prepareStatement("select * from mensajes where id_proyecto = ?");
			ps.setString(1, pid);
			ResultSet rs = ps.executeQuery();
			
			while(rs.next()) {
				
				messageBean aux = new messageBean();
				
				aux.setId(rs.getInt("id_mensaje"));
				aux.setPid(rs.getInt("id_proyecto"));
				aux.setMsg(rs.getString("mensaje"));
				aux.setSupport_by(rs.getString("support_by"));
			
				msgs.add(aux);
			}
			
		}
		catch(SQLException e) {
			System.out.println(e);
			cerrarConexion();
			return null;
		}
		
		cerrarConexion();
		return msgs;
	}
	
	public int newMessage(Integer pid, String msg, String support_by) {
		conexion();
		int status = 0;

		try {

			Connection con = getConnect();

			PreparedStatement ps=con.prepareStatement("insert into mensajes(id_proyecto, mensaje, support_by) values(?,?,?)"); 
			  
			ps.setInt(1,pid); 
			ps.setString(2,msg);
			ps.setString(3,support_by);
			
			status = ps.executeUpdate();
			

		}catch(SQLException e) {
			System.out.println(e);
			cerrarConexion();
			return status;
		}
		
		cerrarConexion();
		return status;
	}
	
	
}