var previousSiretValue;
var newSiretValue;
var previousNumDeclaValue;
var newNumDeclaValue;
var previousRaisonSocialeValue;
var newRaisonSocialeValue;

(function($){
    jQuery(document).ready(function(jQuery) {
        $("#etape-cerfa").attr('src', $("input[name='cerfa-step']").val());
        $("#etape-cerfa").show();
        manageAutocomplete();
        manageNewContactModal();
        displayErrorFields();
        disableSubmitByHittingEnter();
        checkIfContactGotMailAndFunction();
        $("#edit-siret-number").focus(function() {
            previousSiretValue = $(this).val();
        });
        $("#edit-siret-number").change(function() {
            newSiretValue = $(this).val();
            if (newSiretValue != previousSiretValue) {
                jQuery("input[name='id_ref_organisme_formation']").val('');
            }
        });
        $("#edit-activity-number").focus(function() {
            previousNumDeclaValue = $(this).val();
        });
        $("#edit-activity-number").change(function() {
            newNumDeclaValue = $(this).val();
            if (newNumDeclaValue != previousNumDeclaValue) {
                jQuery("input[name='id_ref_organisme_formation']").val('');
            }
        });
        $("#edit-corporate-name").focus(function() {
            previousRaisonSocialeValue = $(this).val();
        });
        $("#edit-corporate-name").change(function() {
            newRaisonSocialeValue = $(this).val();
            if (newRaisonSocialeValue != previousRaisonSocialeValue) {
                jQuery("input[name='id_ref_organisme_formation']").val('');
            }
        });
        
        
    });
})(jQuery)

function displayErrorFields() {
    if (jQuery("input[name='id_ref_organisme_formation']").val() != '') {
        showExistOf();
        if (jQuery("#new-contact-modal input").hasClass('error')) {
            jQuery("#new-contact-modal").modal('show');
        }
    } else {
        showNewOf();
    }
}

function showNewOf() {
    jQuery("#edit-contact").hide();
    jQuery("#print-info-generale").hide();
    jQuery("#edit-info-generale").show();
    jQuery("#edit-new-contact").show();
}

function showExistOf() {
    jQuery("#edit-info-generale").hide();
    jQuery("#edit-new-contact").hide();
    jQuery("#edit-contact").show();
    jQuery("#print-info-generale").show();
}

function completeContact(idOF) {
    jQuery.ajax({
        type: 'GET',
        url: '/dgf/demande/organisme-formation/ajax/get-contact-from-of',
        data: {id_organisme_formation: idOF},
        dataType: 'text',
        error: function(request, status, error) {
            alert(status);
        },
        success: function(data, status, request) {
            var dataJson = jQuery.parseJSON(data);
            jQuery("#edit-select-contact").html('');
            jQuery.each(dataJson, function(k, contactObject) {
                var name = contactObject.civilite + ' ' + contactObject.prenom + ' ' + contactObject.nom;
                name += contactObject.email ? ' (' + contactObject.email + ')' : '';
                if (contactObject.est_contact_principal == '1') {
                    jQuery("#edit-select-contact").append('<option value="' + contactObject.id + '" selected="selected">' + name + '</option>');
                } else {
                    jQuery("#edit-select-contact").append('<option value="' + contactObject.id + '">' + name + '</option>');
                }
            });
        }
    });
}
function myTrim(value) {
    if (value== null) return '';

    return value.trim();
}
function manageAutocomplete() {
    jQuery('#edit-siret-number').autocomplete({
        source: '/dgf/demande/organisme-formation/autocomplete/siret',
        dataType: 'json',
        minLength : 3,
        select: function (event, ui) {
            populateOFFields(ui);
        },
        change: function(event, ui) {
            eraseFieldsVal();
        }
    });

    jQuery('#edit-activity-number').autocomplete({
        source: '/dgf/demande/organisme-formation/autocomplete/activity-number',
        dataType: 'json',
        minLength : 3,
        select: function (event, ui) {
            populateOFFields(ui);
        },
        change: function(event, ui) {
            eraseFieldsVal();
        }
    });

    jQuery('#edit-corporate-name').autocomplete({
        source: '/dgf/demande/organisme-formation/autocomplete/corporate-name',
        dataType: 'json',
        minLength : 3,
        select: function (event, ui) {
            populateOFFields(ui);
        },
        change: function(event, ui) {
            eraseFieldsVal();
        }
    });
}

function populateOFFields(ui) {
    if (ui.item.data.siret) {
        jQuery("#edit-siret-number").val(ui.item.data.siret.trim());
    } else {
        jQuery("#edit-siret-number").val('');
    }
    if (ui.item.data.numero_de_declaration_existence) {
        jQuery("#edit-activity-number").val(ui.item.data.numero_de_declaration_existence.trim());
    } else {
        jQuery("#edit-activity-number").val('');
    }
    if (ui.item.data.raison_sociale) {
        jQuery("#edit-corporate-name").val(ui.item.data.raison_sociale.trim());
    } else {
        jQuery("#edit-corporate-name").val('');
    }
    jQuery("input[name='id_ref_organisme_formation']").val(ui.item.data.id.trim());

    jQuery("#print-info-generale").css("display",'')
    jQuery("#orga-info").html(myTrim(ui.item.data.numero_de_rue) +
                        ' ' + myTrim(ui.item.data.rue) + ' ' +
                            myTrim(ui.item.data.complement_de_rue) + ' '+
                        myTrim(ui.item.data.complement_de_rue_2) + ' '+
                        myTrim(ui.item.data.code_postal) + ' '+
                        myTrim(ui.item.data.ville) + '<br>'+
                        "Téléphone : " + myTrim(ui.item.data.telephone_principal) + '<br>'+
                        "Courriel : " + myTrim(ui.item.data.email) + '<br>'+
                        "Numéro de TVA intracommunautaire : " + myTrim(ui.item.data.tva_intracommunautaire) + '<br>'
    );
    showExistOf();
    
    completeContact(ui.item.data.id.trim());
}

function eraseFieldsVal() {
    jQuery('html').keyup(function(e){
        var key = event.which || event.keyCode;

        if(key == 46 || key == 8) {
            jQuery("input[name='id_ref_organisme_formation']").val('');
            // on réinitialu=ise les chamsp de la partie 1
            if (jQuery('#edit-siret-number').is(':focus')) {
                showNewOf();
                jQuery("#edit-activity-number").val('');
                jQuery("#edit-corporate-name").val('');
                jQuery("#edit-select-contact").html('');
            }
            if (jQuery('#edit-activity-number').is(':focus')) {
                showNewOf();
                jQuery("#edit-siret-number").val('');
                jQuery("#edit-corporate-name").val('');
                jQuery("#edit-select-contact").html('');
            }
            if (jQuery('#edit-corporate-name').is(':focus')) {
                showNewOf();
                jQuery("#edit-activity-number").val('');
                jQuery("#edit-siret-number").val('');
                jQuery("#edit-select-contact").html('');
            }
        }
    });
}

function manageNewContactModal() {
    jQuery("#edit-add").click(function() {
        jQuery("#new-contact-modal").modal('show');
        return false;
    });
    
    jQuery("#edit-modal-save").click(function() {
        if (!checkErrorModalContact()) {
            jQuery("#new-contact-modal").modal('hide');
            populateSelectContactFromModal();
        }
        return false;
    });
}

function disableSubmitByHittingEnter() {
    jQuery(window).keydown(function(event){
        if(event.keyCode == 13) {
          event.preventDefault();
          return false;
        }
    });
}

function checkIfContactGotMailAndFunction() {
    jQuery('#edit-select-contact').change(function(){
        if (jQuery('#edit-direct-payment-1').is(':checked')) {
            var contact = jQuery('#edit-select-contact option:selected').val();
            jQuery.ajax({
                type: 'GET',
                url: '/dgf/ajax/organisme-formation/check-contact-of-infos',
                data: {contact: contact},
           dataType: 'text',
            error: function(request, status, error, data) {
                alert(error);
            },
            success: function(data, status, request) {
                var dataJson = jQuery.parseJSON(data);
                if (dataJson.email == "" || dataJson.id_fonction == "") {
                    jQuery("#complete-contact-modal").modal('show');
                }
            }
        });
        }
    });
}

function checkErrorModalContact() {
    var error = false;
    jQuery("#new-contact-modal .messages-inline").remove();
    jQuery("#new-contact-modal .error").removeClass('error');
    if (jQuery("#edit-modal-contact-title").val() == 0) {
        jQuery(".form-item-modal-contact-title .form-select").addClass('errorCustomSelect');
        jQuery(".form-item-modal-contact-title").append('<div class="messages-inline">Le champ civilité est obligatoire.</div>');
        error = true;
    }
    if (jQuery("#edit-modal-contact-lastname").val() == '') {
        jQuery("#edit-modal-contact-lastname").addClass('error');
        jQuery(".form-item-modal-contact-lastname").append('<div class="messages-inline">Le champ nom est obligatoire.</div>');
        error = true;
    }
    if (jQuery("#edit-modal-contact-firstname").val() == '') {
        jQuery("#edit-modal-contact-firstname").addClass('error');
        jQuery(".form-item-modal-contact-firstname").append('<div class="messages-inline">Le champ prénom est obligatoire.</div>');
        error = true;
    }
    if (jQuery("#edit-modal-contact-fonction").val() == 0) {
        jQuery(".form-item-modal-contact-fonction .form-select").addClass('errorCustomSelect');
        jQuery(".form-item-modal-contact-fonction").append('<div class="messages-inline">Le champ fonction est obligatoire.</div>');
        error = true;
    }
    if (jQuery("#edit-modal-contact-mail").val() == '' && jQuery("#edit-modal-contact-phone").val() == '') {
        jQuery("#edit-modal-contact-mail").addClass('error');
        jQuery("#edit-modal-contact-phone").addClass('error');
        jQuery(".form-item-modal-contact-mail").append('<div class="messages-inline">Le champ email ou téléphone du contact est obligatoire.</div>');
        error = true;
    }
    return error;
}

function populateSelectContactFromModal() {
    var title = jQuery("#edit-modal-contact-title option:selected").text();
    var firstname = jQuery("#edit-modal-contact-firstname").val();
    var lastname = jQuery("#edit-modal-contact-lastname").val();
    var email = jQuery("#edit-modal-contact-mail").val();
    jQuery("#edit-select-contact option[value='0']").remove();
    jQuery("#edit-select-contact").prepend('<option value="0" selected>' + title + ' ' + firstname + ' ' + lastname + ' (' + email + ')</option>');
}
