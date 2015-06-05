(function ($) {
// ------------------------------------  Appel Ajax pour l'administration des paramètres
$("#edit-ref").change(function(event) {
  
  // Valeur du select.
  SelectValue = $(this).val();
  
  // Appel AJAX		  
  $.ajax({
  	    // Appel du loadeer AJAX
    	beforeSend: function() {
    		 $('#loading').show();
    		
  		},
  		complete: function(){
     		$('#loading').hide();
     		
  		},
    	
    	url: '/ajax/ref/' + SelectValue, // Valeurs du select 
        success: function(data) {
        	      $('#resultats').html(data); // Affiche les données  										
			    },
		error: function(error){
		          $('#resultats').html("<h3>Aucun résultat</h3>"); // Affiche les données  	
		       }
	  });
 
});

// Trie du tableau 
$(document).on( "click", "#TableRefId", function() {
  $("#ref_list").stupidtable(); // Trie le tableau  
});
 
// -------------------------- Pagination  ------------------------------------------------------- //
$(document).on( "click", ".pager-first, .pager-next, .pager-previous, .pager-item, .pager-last", function() {
   // Pager URLS
   $url_first = $(".pager-first a:first").prop("href");
   $url_item  = $(".pager-item  a:first").prop("href");
   $url_next  = $(".pager-next  a:first").prop("href");
   $url_last  = $(".pager-last  a:first").prop("href");
   $url_previous  = $(".pager-previouslast  a:first").prop("href");
   
   // Page to display
   if ($url_first) {
   	 $("#resultats").load($url_first);
   }
   if ($url_last) {
   	 $("#resultats").load($url_last);
   }
   if ($url_item) {
   	 $("#resultats").load($url_item);
   }
   if ($url_next) {
   	 $("#resultats").load($url_next);
   }
   if ($url_previous) {
   	 $("#resultats").load($url_previous);
   }
   return false;
});

// -------------------------  End Ajax Call ------------------------------------------- //
}(jQuery));