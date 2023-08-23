/**
 * 
 * @author Oscar Godoy Calderon
 * @brief Clase java para manipular y obtener datos de los usuarios que se registren en la pagina
 * @date 05-01-2020
 */

package es.uco.pw.display.bean;

import java.io.Serializable;

public class CustomerBean implements java.io.Serializable{
	
	private String email = "";
	
	private String password = "";
	
	private String name = "";
	
	private String lastName = "";
	
	private int index = 0;
	
	private int phone = 0;
	
	private String address = "";
	
	private String Province = "";
	
	private String location = "";
	
	private String country = "";
	
	private String profession = "";
	
	private String dni = "";
	
	private String additional_paragraph = "";

	/**
	 * @return the email
	 */
	public String getEmail() {
		return email;
	}

	/**
	 * @param email the email to set
	 */
	public void setEmail(String email) {
		this.email = email;
	}

	/**
	 * @return the password
	 */
	public String getPassword() {
		return password;
	}

	/**
	 * @param password the password to set
	 */
	public void setPassword(String password) {
		this.password = password;
	}

	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}

	/**
	 * @param name the name to set
	 */
	public void setName(String name) {
		this.name = name;
	}

	/**
	 * @return the lastName
	 */
	public String getLastName() {
		return lastName;
	}

	/**
	 * @param lastName the lastName to set
	 */
	public void setLastName(String lastName) {
		this.lastName = lastName;
	}
	
	/**
	 * @return the index
	 */
	public int getIndex() {
		return index;
	}

	/**
	 * @param index the index to set
	 */
	public void setIndex(int index) {
		this.index = index;
	}

	/**
	 * @return the phone
	 */
	public int getPhone() {
		return phone;
	}

	/**
	 * @param phone the phone to set
	 */
	public void setPhone(int phone) {
		this.phone = phone;
	}

	/**
	 * @return the address
	 */
	public String getAddress() {
		return address;
	}

	/**
	 * @param address the address to set
	 */
	public void setAddress(String address) {
		this.address = address;
	}

	/**
	 * @return the province
	 */
	public String getProvince() {
		return Province;
	}

	/**
	 * @param province the province to set
	 */
	public void setProvince(String province) {
		Province = province;
	}

	/**
	 * @return the location
	 */
	public String getLocation() {
		return location;
	}

	/**
	 * @param location the location to set
	 */
	public void setLocation(String location) {
		this.location = location;
	}

	/**
	 * @return the country
	 */
	public String getCountry() {
		return country;
	}

	/**
	 * @param country the country to set
	 */
	public void setCountry(String country) {
		this.country = country;
	}

	/**
	 * @return the profession
	 */
	public String getProfession() {
		return profession;
	}

	/**
	 * @param profession the profession to set
	 */
	public void setProfession(String profession) {
		this.profession = profession;
	}

	/**
	 * @return the id
	 */
	public String getDNI() {
		return dni;
	}

	/**
	 * @param id the id to set
	 */
	public void setDNI(String id) {
		this.dni = id;
	}

	/**
	 * @return the additional_paragraph
	 */
	public String getAdditional_paragraph() {
		return additional_paragraph;
	}

	/**
	 * @param additional_paragraph the additional_paragraph to set
	 */
	public void setAdditional_paragraph(String additional_paragraph) {
		this.additional_paragraph = additional_paragraph;
	}

	@Override
	public String toString() {
		return "CustomerBean [email=" + email + ", password=" + password + ", name=" + name + ", lastName=" + lastName
				+ ", index=" + index + ", phone=" + phone + ", address=" + address + ", Province=" + Province
				+ ", location=" + location + ", country=" + country + ", profession=" + profession + ", dni=" + dni
				+ ", additional_paragraph=" + additional_paragraph + "]";
	}

	
	
	

}