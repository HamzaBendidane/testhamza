(function ($) {
	
/* ---------------------------
 * Show Modal & Close Modal
 * --------------------------*/
function ShowModal(Id) {
  $(Id).modal('show'); 
}
function CloseModal(Id){
  $(Id).modal('hide');	
}

/* ----------------------------------
 * Bouton Ajouter du Haut Call popup 
 * --------------------------------*/
// ADD BUTTON
$(".popup-add").click(function() {
  ShowModal('#popup-add-1'); 
});
// CANCEL BUTTON
$(".CancelButton").click(function() {
  CloseModal('#popup-add-1');
  return false;
});
// ADD BUTTON BOTTOM
$(document).on( "click", ".popup-add-bottom", function() {
   ShowModal('#popup-add-1');
   return false; 
});

/* ----------------------------------
 * Bouton Edit
 * --------------------------------*/

$(document).on( "click", ".popup-edit", function() {
  
  ShowModal("#popup-edit");
  
  tr = $(this).parent().parent(); // Ligne courante
  
  label = tr.children('.libelle'); // Libelle de la ligne

  getlabel = label.text(); // Valeur du label à editer
  
  currId =  tr.children('.idref'); // IDI de la ligne
  
  id_label  = currId.text(); // Id de la  ligne
 
  $('#edit-libelle').val(getlabel);	

  return false; // Bloc Popup
}); 

/* -------------------------------------------
 * Bouton  Valider / Mise à jour popup Editer
 * -----------------------------------------*/
$(document).on( "click", "#btn-update", function() {
  
  new_label =  $('#edit-libelle').val();	// Nouvelle valeur
  
  ref_table =  $('#edit-ref').val();  // Valeur de la table du select

  // Envoie AJAX  
  $.ajax({
  	  	url: '/ajax/ref/edit/' + ref_table + '/' +  id_label + '/' + new_label, // Valeurs du select 
        success: function(data) {
           // $('#resultats').html(data); // Affiche les données  Modal de succès des data		
           alert('Mise à jour reussie');	
           CloseModal("#popup-edit");	
           location.reload();	
		},
		error: function(error){
		  // Erreur lors de la validation
		  alert('Echec Mise à jour');		
		}
  });
});
 
/* -------------------------------------------------------------------
 *  		Bouton  Oui Suppression d'une nature demande
 * -----------------------------------------------------------------*/
$(document).on( "click", "#btn-yes-delete", function() {
  
  ref_table =  $('#edit-ref').val();  // Valeur de la table du select
  
  alert(id_label);
  
  return false;
  // Envoie AJAX  
  $.ajax({
  	  	url: '/ajax/ref/delete/' + ref_table + '/' +  id_label, // Valeurs du select 
        success: function(data) {
           // $('#resultats').html(data); // Affiche les données  Modal de succès des data		
           alert('Suppression reussie');	
           CloseModal("#popup-delete");	
           location.reload();	
		},
		error: function(error){
		  // Erreur lors de la validation
		  alert('Echec Suppression');		
		}
  });
});

/* ----------------------------------
 * Bouton Delete
 * --------------------------------*/
$(document).on( "click", ".popup-delete", function() {
  // Appel popup
  ShowModal("#popup-delete");
  // Block popup
  return false;
}); 

/* ----------------------------------
 * Close Popup
 * --------------------------------*/
$(document).on( "click", "#CloseEdit, #CloseDelete", function() {
    // Fermeture Popup Edit
    var ClosePopupEdit = $('#popup-edit').bPopup();
    
    if (ClosePopupEdit) {
      ClosePopupEdit.close();
    }
    
    // Fermeture Popup Delete
    var ClosePopupDelete = $('#popup-delete').bPopup();
    
    if (ClosePopupDelete) {
      ClosePopupDelete.close();
    }
});
/* ----------------------------------
 * END :) 
 * --------------------------------*/
}(jQuery));