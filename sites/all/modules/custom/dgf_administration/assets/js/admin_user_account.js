(function ($) {
 /** -------------------------------------------
 * Autocompletion de l'autre champ siret
 *---------------------------------------------*/
 //shared_autocomplete('#edit-siret');
  // $('#edit-siret').autocomplete({
          // source: '/autocomplete/siret',
          // dataType: 'json',
          // minLength : 3,
           // select: function( event, ui ) {
      	    // $( "#edit-siret" ).val( ui.item.label );
      	    // }
//       
  // });	
/** -------------------------------------------
 * On charge la page complète avant les filtres
 *---------------------------------------------*/
      // num_demand  = $('#edit-num-demande').val();
	  // nom         = $('#edit-nom').val(); 
	  // prenom      = $('#edit-prenom').val(); 
	  // email       = $('#edit-email').val();
	  // siret       = $('#edit-siret').val();
	  // valid       = $('#edit-valide').val();
  message = "<h4>Aucun résultat n’a été trouvé correspondant à vos critères de recherche.</h4>";
  $.ajax({
	    	url: '/user/management/all',
	        success: function(data) {
	          $('#resultats').html(data); // Affiche les données  										
		    },
			error: function(error){  
			  $('#resultats').html(message); // Affiche les données  		
			}
 });
 
 	  
 /** -------------------------------------------
 * Appel Ajax pour l'administration des paramètres
 *---------------------------------------------*/
 $("#edit-submit").on("click" , function(e) {
	  e.preventDefault(); // Stop submit
	  
	  // Valeur de recherche
	  // num_demand  = $('#edit-num-demande').val();
	  // nom         = $('#edit-nom').val(); 
	  // prenom      = $('#edit-prenom').val(); 
	  // email       = $('#edit-email').val();
	  // siret       = $('#edit-siret').val();
	  // valid       = $('#edit-valide').val();
	  
      message = "<h4>Aucun résultat n’a été trouvé correspondant à vos critères de recherche.</h4>";
      
      searchData = { num_demand : $('#edit-num-demande').val(),
      				 nom: $('#edit-nom').val() ,
      				 prenom: $('#edit-prenom').val(), 
      				 email: $('#edit-email').val(), 
      				 siret: $('#edit-siret').val(), 
      				 valid: $('#edit-valide').val()
      			 };
	  $.ajax({
	  	    // Appel du loadeer AJAX
	    	beforeSend: function() {
	    		 $('#loading').show();
	  		},
	  		complete: function(){
	     		$('#loading').hide();	
	  		},
	  		data: searchData,
	  		type: "POST",
	    	url: '/user/management/',
	        success: function(data) {
	          $('#resultats').html(data); // Affiche les données  										
		    },
			error: function(error){  
			   $('#resultats').html(message);    
			}
		  });
	});
	
  /** ---------------------------------------------
  * Pagination des résultats
  *---------------------------------------------*/
   $(document).on( "click", ".pager-first, .pager-next, .pager-previous, .pager-item, .pager-last", function() {
	   // Pager URLS
	   $url_first = $(".pager-first a:first").prop("href");
	   $url_item  = $(".pager-item  a:first").prop("href");
	   $url_next  = $(".pager-next  a:first").prop("href");
	   $url_last  = $(".pager-last  a:first").prop("href");
	   $url_previous  = $(".pager-previouslast  a:first").prop("href");
	   
	   // alert($url_item);
	   
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
	
	
}(jQuery));