(function ($) {
  // Affichage de Mes établissements
  my_companies = $('#my-companies').html();
  
//  $('#my-companies').hide();

  $('#companies-results').append(my_companies);
	
  $('#edit-cancel').click(function(e) {
  	e.preventDefault;	
  	window.location.replace("/gestion/utilisateurs");
  	return false;
  });
 // Rajoute les étoiles pour les champs obligatoires
 $('#edit-infos label').append('*'); 
 $('#edit-actions .fieldset-legend').append('*');
 
// Check toutes les fonctionnalités
 $('#edit-habilitations-0').click(function(event){
    if(this.checked) { // check select status
            $('.form-checkbox').each(function() { //loop through each checkbox
                this.checked = true;  //select all checkboxes with class "checkbox1"               
            });
        }else{
            $('.form-checkbox').each(function() { //loop through each checkbox
                this.checked = false; //deselect all checkboxes with class "checkbox1"                       
            });         
        }
 });
}(jQuery));

