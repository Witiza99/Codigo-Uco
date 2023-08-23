package es.uco.pw.display.bean;

import java.io.Serializable;

public class messageBean implements Serializable{
	private Integer Id = 0;
	private Integer Pid = 0; //Id del proyecto al que pertenece el mensaje
	private String msg = "";
	private String support_by = "";
	
	public Integer getId() {
		return Id;
	}
	public void setId(Integer id) {
		Id = id;
	}
	public Integer getPid() {
		return Pid;
	}
	public void setPid(Integer pid) {
		Pid = pid;
	}
	public String getMsg() {
		return msg;
	}
	public void setMsg(String msg) {
		this.msg = msg;
	}
	public String getSupport_by() {
		return support_by;
	}
	public void setSupport_by(String support_by) {
		this.support_by = support_by;
	}
}