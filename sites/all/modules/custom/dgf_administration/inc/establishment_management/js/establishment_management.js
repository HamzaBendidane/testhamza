(function($){
	jQuery(document).ready(function($) {
		// validation de la création 
		$('#edit-valid').click(function() {
        	$id = $('#edit-valid').data('id');
            jQuery.ajax({
                cache: false,
                type: 'GET',
                url: '/ajax/gestion/etablissement/valid' + '/' + $id,
                //data: {id: $id}, //, user: user
                dataType: 'text',
                error: function(request, status, error) {
                    alert(status);
                },
                success: function(data, status, request) {
                	// redirection list
                	window.location.href = '/gestion/etablissement/list/';
                }
            });
        });

        // refus de la création
        $('#edit-refuse').click(function() {
        	$id = $('#edit-refuse').data('id');
            jQuery.ajax({
                cache: false,
                type: 'GET',
                url: '/ajax/gestion/etablissement/refuse' + '/' + $id,
                //data: {id: $id}, //, user: user
                dataType: 'text',
                error: function(request, status, error) {
                    alert(status);
                },
                success: function(data, status, request) {
                	// redirection list
//                	window.location.href = '/gestion/validation/etablissement/list/';
                }
            });
        });
	});
})(jQuery)