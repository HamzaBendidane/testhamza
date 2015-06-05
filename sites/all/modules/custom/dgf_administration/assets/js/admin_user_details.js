(function ($) {
  my_companies = $('#my-companies').html();
  
  $('#my-companies').hide();

  $('#companies-results').append(my_companies);
	
  // Check toutes les fonctionnalités
  $( "#edit-habilitations-0" ).on( "click", function() {

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

