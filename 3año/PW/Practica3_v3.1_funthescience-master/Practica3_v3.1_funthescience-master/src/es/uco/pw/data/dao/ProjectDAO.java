package es.uco.pw.data.dao;

import es.uco.pw.display.bean.CustomerBean;
import es.uco.pw.display.bean.ProjectBean;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Properties;
import java.util.ArrayList;
//import java.util.List;

public class ProjectDAO extends ConexionDAO{
	
	
	public ProjectDAO(Properties properties) {
		super(properties);
	}
	
	public ArrayList<ProjectBean> getProjectsByProp(String colum, String search) {
		ArrayList<ProjectBean> projects = new ArrayList<ProjectBean>();
		conexion();
		
		try {
			
			Connection con = getConnect();
			
			String sql = "select * from PROYECTOS where "+ colum;
			
			PreparedStatement ps =  con.prepareStatement(sql+" =?");
			ps.setString(1, search);
			ResultSet rs = ps.executeQuery();
			
			while(rs.next()) {
				
				ProjectBean aux = new ProjectBean();
				
				aux.setId(rs.getInt("indice"));
				aux.setAuthor(rs.getString("nombreAutor"));
				aux.setAuthorMail(rs.getString("correoAutor"));
				aux.setAuthorIndex(rs.getInt("indiceAutor"));
				aux.setObjectiveDonation(rs.getInt("objetivo_donaciones"));				
				aux.setCurrentDonation(rs.getInt("donaciones_actuales"));
				aux.setTitle(rs.getString("nombre"));
				aux.setDescriptionbrief(rs.getString("descripcion_breve"));
				aux.setDescriptionComplete(rs.getString("descripcion"));
				aux.setParticipantes(rs.getString("participantes"));
				aux.setImageProject(rs.getString("imagen"));
				aux.setLogoProject(rs.getString("logo"));
				aux.setCategory(rs.getString("categoria"));
				aux.setDate(rs.getString("date"));
			
				projects.add(aux);
			}
			
		}
		catch(SQLException e) {
			System.out.println(e);
			cerrarConexion();
			return null;
		}
		
		cerrarConexion();
		return projects;
	}
	
	public boolean newProject(ProjectBean cb) {
		conexion();

		try {

			Connection con = getConnect();

			PreparedStatement ps=con.prepareStatement("insert into PROYECTOS values(NULL,?,?,?,?,?,?,?,?,?,?,0,?,?)"); 
			  
			ps.setString(1,cb.getTitle()); 
			ps.setString(2,cb.getDescriptionComplete()); 
			ps.setString(3,cb.getImageProject()); 
			ps.setString(4,cb.getLogoProject()); 
			ps.setString(5,cb.getCategory());
			ps.setString(6,cb.getAuthor());
			ps.setString(7,cb.getAuthorMail());  
			ps.setInt(8,cb.getAuthorIndex()); 
			ps.setString(9,cb.getDescriptionbrief()); 
			ps.setInt(10,cb.getObjectiveDonation());
			ps.setString(11,cb.getParticipantes()); 
			ps.setString(12,cb.getDate()); 
			
			int status = ps.executeUpdate();
			
			PreparedStatement pd =  con.prepareStatement("SELECT indice FROM PROYECTOS WHERE indice=(SELECT max(indice) FROM PROYECTOS)");
			int aux;
			
			ResultSet rs = pd.executeQuery();
			if(rs.first()){
				//aux=rs.getInt("indice");
				cb.setId(rs.getInt("indice"));
				//System.out.println(aux);
			}
			
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
		
		cerrarConexion();
		return true;
	}
	
	public Integer updateProjectByID(String id, String colum, String newCurrent){
		conexion();
		Integer status=0;
		try {
			
			Connection con = getConnect();
			
			String sql = "update PROYECTOS set "+ colum;
			
			PreparedStatement ps =  con.prepareStatement(sql+" =? where indice=?");
			ps.setString(1, newCurrent);
			ps.setString(2, id);
			status = ps.executeUpdate();
				
		}
		catch(SQLException e) {
			System.out.println(e);
			cerrarConexion();
			return status;
		}
		
		cerrarConexion();
		return status;
	}
	
	public ArrayList<ProjectBean> getProjectsWithParticipation(String email){
		ArrayList<ProjectBean> ProjectsWithParticipation = new ArrayList<ProjectBean>();
		conexion();
		try {
			Connection con = getConnect();
			
			String sql = "select * from PROYECTOS where participantes LIKE '%"+email+"%'";
			PreparedStatement ps =  con.prepareStatement(sql);
			ResultSet rs = ps.executeQuery();
			
			while(rs.next()) {
				
				ProjectBean aux = new ProjectBean();
				
				aux.setId(rs.getInt("indice"));
				aux.setAuthor(rs.getString("nombreAutor"));
				aux.setAuthorMail(rs.getString("correoAutor"));
				aux.setAuthorIndex(rs.getInt("indiceAutor"));
				aux.setObjectiveDonation(rs.getInt("objetivo_donaciones"));				
				aux.setCurrentDonation(rs.getInt("donaciones_actuales"));
				aux.setTitle(rs.getString("nombre"));
				aux.setDescriptionbrief(rs.getString("descripcion_breve"));
				aux.setDescriptionComplete(rs.getString("descripcion"));
				aux.setParticipantes(rs.getString("participantes"));
				aux.setImageProject(rs.getString("imagen"));
				aux.setLogoProject(rs.getString("logo"));
				aux.setCategory(rs.getString("categoria"));
				aux.setDate(rs.getString("date"));
			
				ProjectsWithParticipation.add(aux);
			}
		}catch(SQLException e) {
			System.out.println(e);
			cerrarConexion();
			return null;
		}
		cerrarConexion();
		System.out.println(ProjectsWithParticipation.size());
		return ProjectsWithParticipation;
	}
	
	public boolean EliminateProject(String id) {
		conexion();
		try {
			Connection con = getConnect();

			PreparedStatement ps =  con.prepareStatement("DELETE FROM PROYECTOS WHERE indice=?");
			ps.setString(1, id);
			int status = ps.executeUpdate();
			if(status==0) {
				return false;
			}
			
		}catch(SQLException e) {
			System.out.println(e);
			cerrarConexion();
			return false;
		}
		return true;
	}
	
	public ArrayList<String> getMessages(String id) {
		ArrayList<String> msgs = new ArrayList<String>();
		conexion();
		
		try {
			
			Connection con = getConnect();
			
			
			PreparedStatement ps =  con.prepareStatement("select * from mensajes where id_proyecto=?");
			ps.setString(1, id);
			ResultSet rs = ps.executeQuery();
			
			while(rs.next()) {
				
				String aux = new String();
				
				aux = rs.getString("mensaje");
				msgs.add(aux);
				aux = rs.getString("support_by");
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
	
	public ArrayList<ProjectBean> getProjectsIndex(){
		ArrayList<ProjectBean> ProjectsWithParticipation = new ArrayList<ProjectBean>();
		conexion();
		try {
			Connection con = getConnect();
			
			PreparedStatement ps =  con.prepareStatement("select * from PROYECTOS ORDER BY indice DESC LIMIT 0,3");
			ResultSet rs = ps.executeQuery();
			
			while(rs.next()) {
				
				ProjectBean aux = new ProjectBean();
				
				aux.setId(rs.getInt("indice"));
				aux.setAuthor(rs.getString("nombreAutor"));
				aux.setAuthorMail(rs.getString("correoAutor"));
				aux.setAuthorIndex(rs.getInt("indiceAutor"));
				aux.setObjectiveDonation(rs.getInt("objetivo_donaciones"));				
				aux.setCurrentDonation(rs.getInt("donaciones_actuales"));
				aux.setTitle(rs.getString("nombre"));
				aux.setDescriptionbrief(rs.getString("descripcion_breve"));
				aux.setDescriptionComplete(rs.getString("descripcion"));
				aux.setParticipantes(rs.getString("participantes"));
				aux.setImageProject(rs.getString("imagen"));
				aux.setLogoProject(rs.getString("logo"));
				aux.setCategory(rs.getString("categoria"));
				aux.setDate(rs.getString("date"));
			
				ProjectsWithParticipation.add(aux);
			}
		}catch(SQLException e) {
			System.out.println(e);
			cerrarConexion();
			return null;
		}
		cerrarConexion();
		System.out.println(ProjectsWithParticipation.size());
		return ProjectsWithParticipation;
	}
	
	
}
