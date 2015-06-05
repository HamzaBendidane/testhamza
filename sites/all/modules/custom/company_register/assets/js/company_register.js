// We define a function that takes one parameter named $.
(function ($){
    $("#edit-back").click(function() {
        window.history.back();
        return false;
    });
    $("#edit-impression").click(function() {
        window.print();
        return false;
    });
    var htmlEntrepriseInfos = $("#company-register-information-form .company-infos-0").html();
    var i = $("input[name='nb_siret']").val();
    
    // Cache les autres sirets par défaut
    $('#edit-ajout-siret').hide();
    manageAutocomplete('edit-company-siret-0');
    
    if ($("#edit-demande-multi-siret").prop("checked")) {
        $('#edit-ajout-siret').show(); 
    }
    
    // Bouton selectionner demande multiple
    $(document).on("click", "#edit-demande-multi-siret", function(e) {
        $('#edit-ajout-siret').show(); 
        if (!$(this).is(':checked')) {
            $('#edit-ajout-siret').hide();
            $("#autreSiret").html('');
            
            for (var i = 1; i < $("input[name='nb_siret']").val(); i++) {
                $(".company-infos-" + i).remove();
                $("#edit-company hr").remove();
            }
            $("input[name='nb_siret']").val(1);
        }
    });	
  
  // Bouton Ajouter Siret
  $(document).on("click", "#edit-ajout-siret", function(e) {
      e.preventDefault();
      $('#autreSiret').append('<div class="company-infos company-infos-' + i + '">' + htmlEntrepriseInfos + '</div>');
      $('#autreSiret .company-infos-'+i+' .form-item').each(function() {
          var elementClass = $(this).attr('class');
          var newElementClass = elementClass.substr(0, elementClass.length - 1) + i;
          $(this).removeClass(elementClass).addClass(newElementClass);
      });
      $('#autreSiret .company-infos-'+i+' label').each(function() {
          var elementFor = $(this).attr('for');
          var newElementFor = elementFor.substr(0, elementFor.length - 1) + i;
          $(this).attr('for', newElementFor);
      });
      $('#autreSiret .company-infos-'+i+' input').each(function() {
          var elementId = $(this).attr('id');
          var newElementId = elementId.substr(0, elementId.length - 1) + i;
          $(this).attr('id', newElementId);
          var elementName = $(this).attr('name');
          var newElementName = elementName.substr(0, elementName.length - 1) + i;
          $(this).attr('name', newElementName);
          $(this).val('');
      });
      manageAutocomplete('edit-company-siret-'+i);
      i++;
      $("input[name='nb_siret']").val(i);
  });
  
  // Bouton retour
  $('#btn-update').click(function(e) {
    this.disabled = true;
  });

  // Disable print button - Empêche le submit
  $('#PrintBtn').click(function(e) {
    this.disabled = true;
  });
  
  // Check toutes les fonctionnalités
  $( "#edit-fonctionsutilisateur-0" ).on( "click", function() {
    if(this.checked) { // check select status
        $('.form-checkbox').each(function() { //loop through each checkbox
            this.checked = true;  //select all checkboxes with class "checkbox1"               
        });
    } else {
        $('.form-checkbox').each(function() { //loop through each checkbox
            this.checked = false; //deselect all checkboxes with class "checkbox1"                       
        });         
    }
  });
}(jQuery));

function manageAutocomplete(elementId) {
    jQuery("#"+elementId).autocomplete({
        source: '/autocomplete/siret',
        dataType: 'json',
        minLength : 3,    
        select: function( event, ui ) {
            var elementNumber = elementId.substr(elementId.length - 1);
            jQuery( "#edit-company-siret-"+elementNumber).val( ui.item.label );
            //  On préremplie les champs
            jQuery("#edit-company-raison-sociale-"+elementNumber).val( ui.item.data.raison_sociale);
            jQuery( "#edit-company-adresse-street-number-"+elementNumber).val( ui.item.data.numero_de_rue);
            jQuery( "#edit-company-adresse-street-name-"+elementNumber).val(ui.item.data.rue);
            jQuery( "#edit-company-adresse-street-namemore-"+elementNumber).val( ui.item.data.complement_de_rue);
            jQuery( "#edit-company-adresse-town-"+elementNumber).val( ui.item.data.ville);
            jQuery( "#edit-company-code-postal-"+elementNumber).val( ui.item.data.code_postal);
            jQuery( "#edit-company-telephone-"+elementNumber).val( ui.item.data.telephone_principal );
            jQuery( "#edit-code-naf-"+elementNumber).val( ui.item.data.id_naf );
            return false;
        }
    });
}