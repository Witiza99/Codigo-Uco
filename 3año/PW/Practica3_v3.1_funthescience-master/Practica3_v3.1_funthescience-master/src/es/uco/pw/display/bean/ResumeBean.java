/**
 * 
 * @author Oscar Godoy Calderon
 * @brief Clase java para la recepcion y tratamiento de datos para los CV
 * @date 05-01-2020
 */

package es.uco.pw.display.bean;

import java.io.Serializable;

public class ResumeBean implements Serializable{

		private int id = 0;
		
		private String fullName = "";
		
		private String brief_intro = "";
		
		private String address = "";
		
		private String email = "";
		
		private int phone = 0;
		
		private String experience_professional = "";
		
		private String languages = "";
		
		private String programming = "";
		
		private String studies = "";
		
		private String referer = "";
		
		private int id_user = 0;
		
		private int show_cv = 0;

		/**
		 * @return the id
		 */
		public int getId() {
			return id;
		}

		/**
		 * @param id the id to set
		 */
		public void setId(int id) {
			this.id = id;
		}

		/**
		 * @return the fullName
		 */
		public String getFullName() {
			return fullName;
		}

		/**
		 * @param fullName the fullName to set
		 */
		public void setFullName(String fullName) {
			this.fullName = fullName;
		}

		/**
		 * @return the brief_intro
		 */
		public String getBrief_intro() {
			return brief_intro;
		}

		/**
		 * @param brief_intro the brief_intro to set
		 */
		public void setBrief_intro(String brief_intro) {
			this.brief_intro = brief_intro;
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
		 * @return the experience_professional
		 */
		public String getExperience_professional() {
			return experience_professional;
		}

		/**
		 * @param experience_professional the experience_professional to set
		 */
		public void setExperience_professional(String experience_professional) {
			this.experience_professional = experience_professional;
		}

		/**
		 * @return the languages
		 */
		public String getLanguages() {
			return languages;
		}

		/**
		 * @param languages the languages to set
		 */
		public void setLanguages(String languages) {
			this.languages = languages;
		}

		/**
		 * @return the programming
		 */
		public String getProgramming() {
			return programming;
		}

		/**
		 * @param programming the programming to set
		 */
		public void setProgramming(String programming) {
			this.programming = programming;
		}

		/**
		 * @return the studies
		 */
		public String getStudies() {
			return studies;
		}

		/**
		 * @param studies the studies to set
		 */
		public void setStudies(String studies) {
			this.studies = studies;
		}

		/**
		 * @return the referer
		 */
		public String getReferer() {
			return referer;
		}

		/**
		 * @param referer the referer to set
		 */
		public void setReferer(String referer) {
			this.referer = referer;
		}

		/**
		 * @return the id_user
		 */
		public int getId_user() {
			return id_user;
		}

		/**
		 * @param id_user the id_user to set
		 */
		public void setId_user(int id_user) {
			this.id_user = id_user;
		}

		/**
		 * @brief controlBean control de las propiedades del bean que no esten por defecto
		 * @return boolean 
		 */
		public boolean controlBean() {
			if(this.fullName == "" || this.brief_intro == "" || this.address == "" || this.email == "" || !checkPhone(this.phone) || this.experience_professional == "" || this.languages == ""
					|| this.programming == "" || this.studies == "" || this.referer == "") {
				return false;
			}
			return true;
		}
		
		/**
		 * 
		 * @brief retorna falso en caso tenga menos de 9 digitos y verdadero en caso sea igual a 9
		 * @param phone numero de movil para constatar que tiene 9 digitos
		 * @return
		 */
		public boolean checkPhone(int phone) {
			String s_phone = Integer.toString(phone);
			if(s_phone.length() == 9) {
				return true;
			}
			return false;
		}
		

		/**
		 * @return the show_cv
		 */
		public int getShow_cv() {
			return show_cv;
		}

		/**
		 * @param show_cv the show_cv to set
		 */
		public void setShow_cv(int show_cv) {
			this.show_cv = show_cv;
		}

		/**
		 * 
		 * @brief metodo para imprimir los valores de las propiedades de la clase ResumeBean
		 * @return String
		 */
		@Override
		public String toString() {
			return "ResumeBean [id=" + id + ", fullName=" + fullName + ", brief_intro=" + brief_intro + ", address="
					+ address + ", email=" + email + ", phone=" + phone + ", experience_professional="
					+ experience_professional + ", languages=" + languages + ", programming=" + programming
					+ ", studies=" + studies + ", referer=" + referer + ", id_user=" + id_user + "]";
		}
		
		
}