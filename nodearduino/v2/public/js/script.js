io = io.connect('/browsers')

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

// Listen for the talk event.
io.on('rotaenviousuario', function(data) {
	var led = data.led;
    if(led=="1a"){
    	$('#botao').text('Desligar');
    }else if(led=="0a") {
    	$('#botao').text('Ligar');
    }
})
