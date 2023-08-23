package es.uco.pw.display.bean;

import java.io.Serializable;
import java.util.List;

public class ProjectBean implements Serializable{
	
	private Integer Id = 0;
	
	private String author = "";
	
	private String authorMail= "";	
	
	private Integer authorIndex= 0;
	
	private Integer objectiveDonation= 0;
	
	private Integer currentDonation= 0;
	
	private String title= "";
	
	private String descriptionbrief= "";
	
	private String descriptionComplete= "";
	
	private String participantes= "";
	
	private String webPages= "";
	
	private String imageProject= "";
	
	private String logoProject= "";
	
	private String category = "";
	
	private String date;
	
	private String status = "";

	public void ProjectBean() {
		
	}
	
	/**
	 * @return the id
	 */
	public Integer getId() {
		return Id;
	}
	
	/**
	 * @param Id the Id to set
	 */
	public void setId(Integer Id) {
		this.Id = Id;
	}
	
	/**
	 * @return the authorMail
	 */
	public String getAuthorMail() {
		return authorMail;
	}

	/**
	 * @param authorMail the authorMail to set
	 */
	public void setAuthorMail(String authorMail) {
		this.authorMail = authorMail;
	}
	
	/**
	 * @return the authorIndex
	 */
	public Integer getAuthorIndex() {
		return authorIndex;
	}

	/**
	 * @param authorIndex the authorIndex to set
	 */
	public void setAuthorIndex(Integer authorIndex) {
		this.authorIndex = authorIndex;
	}
	
	/**
	 * @return the objectiveDonation
	 */
	public Integer getObjectiveDonation() {
		return objectiveDonation;
	}

	/**
	 * @param objectiveDonation the objectiveDonation to set
	 */
	public void setObjectiveDonation(Integer objectiveDonation) {
		this.objectiveDonation = objectiveDonation;
	}
	
	/**
	 * @return the currentDonation
	 */
	public Integer getCurrentDonation() {
		return currentDonation;
	}

	/**
	 * @param currentDonation the currentDonation to set
	 */
	public void setCurrentDonation(Integer currentDonation) {
		this.currentDonation = currentDonation;
	}
	
	/**
	 * @return the author
	 */
	public String getAuthor() {
		return author;
	}

	/**
	 * @param author the author to set
	 */
	public void setAuthor(String author) {
		this.author = author;
	}


	/**
	 * @return the title
	 */
	public String getTitle() {
		return title;
	}

	/**
	 * @param title the title to set
	 */
	public void setTitle(String title) {
		this.title = title;
	}

	/**
	 * @return the descriptionbrief
	 */
	public String getDescriptionbrief() {
		return descriptionbrief;
	}

	/**
	 * @param descriptionbrief the descriptionbrief to set
	 */
	public void setDescriptionbrief(String descriptionbrief) {
		this.descriptionbrief = descriptionbrief;
	}

	/**
	 * @return the descriptionComplete
	 */
	public String getDescriptionComplete() {
		return descriptionComplete;
	}

	/**
	 * @param descriptionComplete the descriptionComplete to set
	 */
	public void setDescriptionComplete(String descriptionComplete) {
		this.descriptionComplete = descriptionComplete;
	}

	/**
	 * @return the participantes
	 */
	public String getParticipantes() {
		return participantes;
	}

	/**
	 * @param participantes the participantes to set
	 */
	public void setParticipantes(String participantes) {
		this.participantes = participantes;
	}

	/**
	 * @return the webPages
	 */
	public String getWebPages() {
		return webPages;
	}

	/**
	 * @param webPages the webPages to set
	 */
	public void setWebPages(String webPages) {
		this.webPages = webPages;
	}

	/**
	 * @return the imageProject
	 */
	public String getImageProject() {
		return imageProject;
	}

	/**
	 * @param imageProject the imageProject to set
	 */
	public void setImageProject(String imageProject) {
		this.imageProject = imageProject;
	}

	/**
	 * @return the logoProject
	 */
	public String getLogoProject() {
		return logoProject;
	}

	/**
	 * @param logoProject the logoProject to set
	 */
	public void setLogoProject(String logoProject) {
		this.logoProject = logoProject;
	}

	/**
	 * @return the category
	 */
	public String getCategory() {
		return category;
	}

	/**
	 * @param category the category to set
	 */
	public void setCategory(String category) {
		this.category = category;
	}
	
	/**
	 * @return the date
	 */
	public String getDate() {
		return date;
	}

	/**
	 * @param date the date to set
	 */
	public void setDate(String date) {
		this.date = date;
	}
	@Override
	public String toString() {
		return "ProjectBean [author=" + author + ", authorMail=" + authorMail + ", authorIndex=" + authorIndex
				+ ", objectiveDonation=" + objectiveDonation + ", currentDonation=" + currentDonation + ", title="
				+ title + ", descriptionbrief=" + descriptionbrief + ", descriptionComplete=" + descriptionComplete
				+ ", participantes=" + participantes + ", webPages=" + webPages + ", imageProject=" + imageProject
				+ ", logoProject=" + logoProject + ", category=" + category + ", date=" + date + ", status=" + status
				+ "]";
	}

	/**
	 * @return the status
	 */
	public String getStatus() {
		return status;
	}

	/**
	 * @param date the date to set
	 */
	public void setStatus(String status) {
		this.status = status;
	}
	
}