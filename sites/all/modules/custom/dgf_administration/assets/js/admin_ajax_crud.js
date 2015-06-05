(function ($) {
// ------------------------------------ BEGIN AJAX CRUD ----------------------------------------- //
	
//----------------------- Validation et envoie des donner ------------------------- //

$(document).on("click", "#valider" , function(){
  // Label saisie	
  var ref_label = $('#edit-label').val();
  // Valeur du select
  var ref_table = $('#edit-ref').val();
   	
  $.ajax({
  	    type: 'POST',
        url:  "/ajax/ref/add/" + ref_table + '/' + ref_label, // Fonction d'insertion en BD'
        success: function(){
           
           $('popup-add-1').modal('hide');
        },
        error:function(){
            $('popup-add-1').modal('show');
        }
    });    
});

//----------------------- Suppression des données -------------------------------- //

$(document).on("click", "#delete" , function(){
  // ID TABLE
  var ref_table = $('#edit-ref').val(); 
  
  // ID ROW
  $("#ref_list").each(function (){
  
  // Id de la ligne
  var row_id  = $('td').attr('data-id');   
  
  // alert(row_id);
  
  return false;
  });
  
  // BEGIN VALIDATE BUTTON
  $('#RefDelete').click(function (){
 
  	// AJAX CALL FOR DELETE
	  $.ajax({
	  	    type: 'POST',
	        url:  "/ajax/ref/delete/" + ref_table + '/' + row_id, // Fonction d'insertion en BD'
	        success: function(){
	            // alert("Données insérés avec succès");
	           alert('Suppréssion reussie');
	        },
	        error:function(){
	           alert('Suppréssion échoué');
	        }
	    });  
	  // END OF AJAX CALL 
  });
  // END VALIDATE BUTTON
});


//----------------------- Modification des données -------------------------------- //
$(document).on("click", "#edit" , function(){
  // Id de la ligne
  var row_id = $('#idref').text();
 
  // BEGIN VALIDATE BUTTON
  $('#RefConfirm').click(function (){
  	  // LABEL A INSERER
  	  var ref_label = $('#EditLibelle').val();
  	  
  	  // ID TABLE REF
      var ref_table = $('#edit-ref').val(); 
  	 
  	  // APPEL AJAX
  	  return false;
      $.ajax({
  	    type: 'POST',
        url:  "/ajax/ref/edit/" +  ref_table + '/' + row_id + '/' + ref_label, // Fonction d'insertion en BD'
        success: function(){
            // alert("Données insérés avec succès");
           alert('Suppréssion reussie');
        },
        error:function(){
           alert('Suppréssion échoué');
        }
    });  	
    // END AJAX CALL
  });
  
});
// ----------------------------- END 0F AJAX CRUD ------------------------------------------ // 
}(jQuery));