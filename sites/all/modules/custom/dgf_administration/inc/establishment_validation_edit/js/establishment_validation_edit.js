(function($){
	jQuery(document).ready(function($) {
		// validation de la création 
//		$('#edit-valid').click(function() {
//        	$idEntreprise = $('#edit-valid').data('id-entreprise');
//        	$idContact = $('#edit-valid').data('id-contact');
//        	$idAddress = $('#edit-valid').data('id-adresse');
//            jQuery.ajax({
//                cache: false,
//                type: 'GET',
//                url: '/ajax/gestion/etablissement/valid' + '/' + $idEntreprise + '/' + $idContact + '/' + $idAddress,
//                //data: {id: $id}, //, user: user
//                dataType: 'text',
//                error: function(request, status, error) {
//                    alert(status);
//                },
//                success: function(data, status, request) {
//                	// redirection list
//                	window.location.href = '/gestion/etablissement/list/';
//                }
//            });
//        });

        // refus de la création
//        $('#edit-refuse').click(function() {
//        	$idEntreprise = $('#edit-valid').data('id-entreprise');
//        	$idContact = $('#edit-valid').data('id-contact');
//        	$idAddress = $('#edit-valid').data('id-adresse');
//            jQuery.ajax({
//                cache: false,
//                type: 'GET',
//                url: '/ajax/gestion/etablissement/refuse' + '/' + $idEntreprise + '/' + $idContact + '/' + $idAddress,
//                //data: {id: $id}, //, user: user
//                dataType: 'text',
//                error: function(request, status, error) {
//                    alert(status);
//                },
//                success: function(data, status, request) {
//                	// redirection list
////                	window.location.href = '/gestion/validation/etablissement/list/';
//                }
//            });
//        });

        $('#edit-cancel').click(function() {
        	window.location = "/validation/etablissement/list";
        });
	});
})(jQuery)