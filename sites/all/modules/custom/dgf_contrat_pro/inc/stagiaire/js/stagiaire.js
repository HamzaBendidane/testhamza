(function($){
    jQuery(document).ready(function($) {
        $("#etape-cerfa").attr('src', $("input[name='cerfa-step']").val());
        $("#etape-cerfa").show();
        
        var dob = $("#edit-birthday").val();
        if (dob.length == 10) {
            var age = get_age(dob);
            $("#edit-age").val(age);
        }
        
        $("#edit-plus-26-ans").toggle($("#edit-pole-emploi-number").val() == '' && parseInt($("#edit-age").val()) >= 26);
        
        toggle_pole_emploi_fields();
        
        var now = new Date();
        
        jQuery('.datePicker').datepicker({
            format: 'dd/mm/yyyy',
            language: 'fr',
            endDate: new Date(),
            orientation: 'right',
            defaultViewDate: {
                year: now.getFullYear() - 18,
                month: now.getMonth(),
                day: now.getDate()
            }
        }).on('changeDate', function(e) {
           // $(this).datepicker('hide');
            var dob = $("#edit-birthday").val();
            if (dob.length == 10) {
                var age = get_age(dob);
                $("#edit-age").val(age);
            }
        });

        // Autocompletion du champ siret
        $('#edit-lastname').autocomplete({
            source: '/autocomplete/get-salarie-from-name',
            dataType: 'json',
            minLength : 3,
            select: function( event, ui ) {
                $("#edit-lastname" ).val( ui.item.data.nom.trim());
                $("#edit-firstname" ).val(ui.item.data.prenom.trim());
                $("#edit-birthday" ).val(ui.item.data.date_de_naissance);
                $("#edit-age" ).val(get_age(ui.item.data.date_de_naissance));
                $("input[name='id_salarie']").val(ui.item.data.id.trim());

                if (ui.item.data.id_civilite && ui.item.data.id_civilite.trim() == 'Mme') {
                    $("#edit-man-woman-mme").prop("checked", true);
                } else {
                    $("#edit-man-woman-m").prop("checked", true);
                }

                if (ui.item.data.est_travailleur_handicape && ui.item.data.est_travailleur_handicape.trim() == '1') {
                    $("#edit-handicapped-worker-1").prop("checked", true);
                } else {
                    $("#edit-handicapped-worker-0").prop("checked", true);
                }
                
//                // TODO : données à ne pas remplir :
//                $("#edit-highest-level").val();
//                $("#edit-social-beneficiary").val();
//                $("#edit-last-status").val();
//                $("#edit-pole-emploi-number").val();
//                $("#edit-since-month").val();
//                $("#edit-pension-fund").val();
//                $("#edit-contingency-fund").val();
//                $("#edit-info-juridique").val();
//                
//                // TODO : données manquantes dans le référentiel :
//                $("#edit-address" ).val();
//                $("#edit-zip-code" ).val();
//                $("#edit-city" ).val();
//                $("#edit-phone-number").val();
//                $("#edit-email").val();
                
                return false;
            }
        });
        
        $("#edit-pole-emploi-number").change(function() {
            $("#edit-plus-26-ans").toggle($("#edit-pole-emploi-number").val() == '' && parseInt($("#edit-age").val()) >= 26);
        });

        // gestion de la modale de validation
        $('#edit-quit').click(function() {
            $("#modalquit").modal("show");
        });

        //tooltip
        $('#juridique_info').tooltip({
            placement : 'top'
        });
        $('#highest_level_tooltip').tooltip({
            placement : 'top'
        });
    });
    
    $("#edit-last-status").change(function(){
    	toggle_pole_emploi_fields();
    });
    
    function toggle_pole_emploi_fields() {
    	$(".form-item-pole-emploi-number, .form-item-since-month").toggle($("#edit-last-status").val() == 9 || $("#edit-last-status").val() == 10);
    }
    
    function get_age(born) {
        var now = new Date();
        var birthdate = born.split("/");
        var born = new Date(birthdate[2], birthdate[1]-1, birthdate[0]);
        var birthday = new Date(now.getFullYear(), born.getMonth(), born.getDate());
        var age;
        if (now >= birthday) {
          age = now.getFullYear() - born.getFullYear();
        } else {
          age = now.getFullYear() - born.getFullYear() - 1;
        }
        
        $("#edit-plus-26-ans").toggle(age >= 26 && $("#edit-pole-emploi-number").val() == '');
        return age;
    }

})(jQuery)