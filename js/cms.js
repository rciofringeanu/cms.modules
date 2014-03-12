(function($){
    
    $(document).ready(function(){
        $('#item').change(function(){
            if (this.value) window.location.href=this.value;
        })
    });
})(jQuery);
