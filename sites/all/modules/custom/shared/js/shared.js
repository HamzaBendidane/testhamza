// Fonctions génériques JS
(function ($) {
  // JS AUTOCOMPLETE	
  function shared_autocomplete(ElementId) {
    this.autocomplete({
      source: '/autocomplete/siret',
      dataType: 'json',
      minLength : 3, 	
      select: function( event, ui ) {
      	$(ElementId).val( ui.item.label );
        //  On préremplie les champs
        //  rue = ui.item.data.rue;
        //  nomRue = rue.replace(/\d+/g, '');
        // complementRue = ui.item.data.complement_de_rue.replace(/\d+/g, '');
        $("#edit-companyraisonsociale").val( ui.item.data.raison_sociale);
        // Adresse entreprises
        $( "#edit-companyadressestreetnumber" ).val( ui.item.data.numero_de_rue);
        $( "#edit-companyadressestreetname" ).val(ui.item.data.rue.replace(/\d+/g, ''));
        $( "#edit-companyadressestreetnamemore" ).val( ui.item.data.complement_de_rue.replace(/\d+/g, ''));
        $( "#edit-companyadressetown" ).val( ui.item.data.ville);
        $( "#edit-companycodepostal" ).val( ui.item.data.code_postal);
        $( "#edit-companytelephone" ).val( ui.item.data.telephone_principal );
        $( "#edit-codenaf" ).val( ui.item.data.id_naf );
        $( "#edit-codenace" ).val( ui.item.data.id_nace);
      	return false;
      }
    });
  } 
  
  //Remove error class on radio click
  $(".form-type-radio").click(function() {
    $(this).closest(".form-type-radios").find(".form-radio").removeClass("error");
  });
  
}(jQuery));