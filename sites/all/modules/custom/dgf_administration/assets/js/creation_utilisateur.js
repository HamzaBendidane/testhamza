(function ($) {
  // Check toutes les fonctionnalités
  $("#add_company").hide();
  
  $( "#edit-rattacher" ).on( "click", function(e) {
  	e.preventDefault();
    $( "#add_company" ).toggle( "slow" );
  });
  
  $( ".btn-danger" ).on( "click", function(e) {
 	 $( "#add_company" ).hide();
  });
  
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