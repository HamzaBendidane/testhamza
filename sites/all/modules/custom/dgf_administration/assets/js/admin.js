(function ($) {
/*
Drupal.behaviors.dgf_administration = {
 
  // this behavior function is called when new element is being added.
attach: function (context, settings) {
    // Do your js stuffs you want to do after your AJAX call.
    // Gestion des selects pour les paramètres
$( "#edit-ref" ).change(function(event) {
  // Valeur du select.
  SelectValue = $(this).val();
	  
  $.ajax({
    	url: '/opcaim/ref/' + SelectValue, // Valeurs du select 
    	complete: function(data) {
    		console.log('complete');
    		},
			    success: function(data) {
			    	console.log(data);
			        if (data) {
			          $('#resultats').html(data);
			          alert('inside');
			        } else {
			        	alert('No data');
			        }
			    },
			    error: function(jqXHR, textStatus, errorThrown){
		            console.log(jqXHR);
		            console.log(textStatus);
		            console.log(errorThrown);
		        }
	  });
  });
    
  }
};*/


$("#edit-ref").change(function(event) {
  // Valeur du select.
  SelectValue = $(this).val();
	  
  $.ajax({
    	url: '/opcaim/ref/' + SelectValue, // Valeurs du select 
    	complete: function(data) {
    		console.log('complete');
    		},
			    success: function(data) {
			    	console.log(data);
			        if (data) {
			          $('#resultats').html(data);
			          alert('inside');
			        } else {
			        	alert('No data');
			        }
			    },
			    error: function(jqXHR, textStatus, errorThrown){
		            console.log(jqXHR);
		            console.log(textStatus);
		            console.log(errorThrown);
		        }
	  });
  });
// Call popup
$( "#edit-pop" ).click(function() {
  // Autre siret
  $('#mod').bPopup({
  	        closeClass:'Fermer',
            contentContainer:'',
            //loadUrl: 'http://dev.opcaim2/gestion/opcaim/mon-compte' //Uses jQuery.load()
  }); 
  // Block popup
  return false;
});

// Close Popup
// Todo Close button
// End Popup

// Gestion des selects pour les paramètres
/*
$( "#edit-ref" ).change(function(event) {
	  // Valeur du select.
	  SelectValue = $(this).val();
	  
	  $.ajax({
			    type:'GET',
			    url: '/opcaim/ref/' + SelectValue, // Valeurs du select 
			    dataType: "html",
			    complete: function(data) {
			    	console.log('complete');
			    },
			    success: function(data) {
			    	console.log(data);
			        if (data) {
			          $('#resultats').html(data);
			          alert('inside');
			        } else {
			        	alert('No data');
			        }
			    },
			    error: function(jqXHR, textStatus, errorThrown){
		            console.log(jqXHR);
		            console.log(textStatus);
		            console.log(errorThrown);
		        }
	  });
  //});

//----------- End of functions
});
*/

}(jQuery));