(function($){
    jQuery(document).ready(function($) {
        $("#etape-cerfa").attr('src', $("input[name='cerfa-step']").val());
        $("#etape-cerfa").show();
        
        $("#vaBeneficierFormation").hide();
        jQuery('.datePicker').datepicker({
            format: 'dd/mm/yyyy',
            language: 'fr',
        }).on('changeDate', function(e) {
            $(this).datepicker('hide');
        });
        
        if ($("input[name='modal']").val() == 'certification_tuteur') {

            if($("input[class='form-text error']").length == 0){
                $("#modal-certification-tuteur").modal("show");
            };
        }
        
        if ($("input[name='modal']").val() == 'message_information_final') {
            $("#modal-message-information-final").modal("show");
        }
       
        // gestion de la modale de validation
        $('#edit-quit').click(function() {
            $("#modalquit").modal("show");
        });
        
        $("#edit-modal-annuler").click(function() {
            $("#modal-certification-tuteur").modal("hide");
            return false;
        });

         $('#va_beneficier_info').tooltip({
             placement : 'bottom'
         });
         
         $( "#edit-beneficier-1" ).click(function() {
             $("#vaBeneficierFormation").show();
         });
         
        $( "#edit-beneficier-0" ).click(function() {
             $("#vaBeneficierFormation").hide();
             $("#edit-date-formation").val('');
             $("#edit-duree-formation").val('');
             $("#edit-nom-organisme").val('');
        });
        
        if ($( "#edit-beneficier-1" ).is(":checked")) {
            $("#vaBeneficierFormation").show();
        }
        
        // Autocompletion du champ siret
        $('#edit-lastname').autocomplete({
            source: '/autocomplete/get-salarie-from-name',
            dataType: 'json',
            minLength : 3,
            select: function( event, ui ) {console.log(ui.item.data);
                $("#edit-lastname" ).val( ui.item.data.nom.trim());
                $("#edit-firstname" ).val(ui.item.data.prenom.trim());
                $("#edit-birthday" ).val(ui.item.data.date_de_naissance);
                $("input[name='id_salarie']").val(ui.item.data.id.trim());
                if (ui.item.data.id_niveau_de_formation_actuel) {
                    $("#edit-dernier-diplome").val(ui.item.data.id_niveau_de_formation_actuel.trim());
                }

                return false;
            }
        });
        
        if ($(".form-item-dateFormation input").hasClass("error")
                || $(".form-item-dureeFormation input").hasClass("error")
                || $(".form-item-nomOrganisme input").hasClass("error")) {
            $("#vaBeneficierFormation").show();
        }
    });
})(jQuery)