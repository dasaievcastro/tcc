jQuery(document).ready(function($){
	io = io.connect()
	var led = 0;

	// Emit ready event.
	$('#botao').click(function(){
		if(led==0){
			led=1;
		}else{
			led=0;
		}
		io.emit('rotapadrao',{led:led}) 
	})


	//io.emit('rotapadrao2') 

	// Listen for the talk event.
	io.on('rotaenviousuario', function(data) {
		var led = data.led;
	    if(led=="1a"){
	    	$('#botao').text('Desligar');
	    }else if(led=="0a") {
	    	$('#botao').text('Ligar');
	    }
	})
})
  
