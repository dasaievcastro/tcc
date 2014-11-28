jQuery(document).ready(function($){
	
	//$('#dimension-switch').bootstrapSwitch('size', 'large');// Sets a large switch
	//$('#change-color-switch').bootstrapSwitch('onColor', 'primary');
	//$('#change-color-switch').bootstrapSwitch('offColor', 'default');

	io = io.connect('http://192.168.1.2:8087')

	var led = 0;

	// Emit ready event.

	io.emit('statusBanco');

	io.on('atualizarAoLigar', function(datas) {
		console.log(datas);
		for(var data in datas){
			var row = datas[data];
			data = data.replace("Ligado", "");
			data = data.replace("Desligado", "");
			data = data.replace("ON", "");
			data = data.replace("OFF", "");
			var status = 2;
			if(row==1){
				status=1;
			}
			if(String(data).indexOf("cor")>=0 && data.indexOf("cora")<0){
				status=3;
			}
			if(data=="temperatura"){
				status=4;
			}
			var texto = $('#'+data).text();
			if(status == 2){
				    texto = texto.replace("Ligada", "Desligada");
				    $('#'+data).text(texto);
				    $('#'+data).removeClass("btn-success");

		    }else if(status == 1){
		    		texto = texto.replace("Desligada", "Ligada");
				    $('#'+data).text(texto);
					$('#'+data).addClass("btn-success");
		    }else if(status==3){
			    $('.btncolor').each(function(){
					var esse = $(this);
					var cor = esse.data('color');

					if(cor==row){
						$('.btncolor').removeClass("active");
						esse.addClass("active")
					}
				})
			}else{
				var temp = parseInt(row);
				$('.progress-bar span').html(parseFloat(row).toFixed(1)+"º C");
				$('.progress-bar').removeClass('progress-bar-danger progress-bar-warning progress-bar-success');
				if(temp>=50){
					$('.progress-bar').addClass('progress-bar-danger');
				}
				if(temp>30 && temp<50){
					$('.progress-bar').addClass('progress-bar-warning');
				}
				if(temp<30){
					$('.progress-bar').addClass('progress-bar-success');
				}
				$('.progress-bar').css('width',temp+"%")
			}
		}
	})


	$('.btncolor').click(function(){
		var color = $(this).data('color');
		io.emit('rotapadrao',{valor:'novacor'+color})
	})


	$('.btn').click(function(event){// se clicar no elemento com id #botao assume o valor abaixo e
		
		event.preventDefault();
		var id = $(this).attr('id'); // cria variavel e armazena valor do boto que cliquei
		
		var texto = $('#'+id).text(); // armazena texto do id quarto (era = '#quarto')
	//alert(texto);

		if(texto == "Ligada"){
			io.emit('rotapadrao', {valor: id+'OFF'})//envia pela rota padrao o valor de id para o arduino
		}else if(texto == "Desligada"){
			io.emit('rotapadrao', {valor: id+'ON'})//envia pela rota padrao o valor de id para o arduino
		}		
	})

	// Listen for the talk event. // ele fica escutando a mensagem do app.js, só que quem envia é o arduíno
	io.on('rotaenviousuario', function(data) {
		var led = data.led;
	    if(led=="1a"){
	    	$('#botao').text('Desligar');
	    }else if(led=="0a") {
	    	$('#botao').text('Ligar');
	    }
	})
	io.on('rotadeescuta', function (data) {
		var status =0;


		if(data.indexOf("Ligado") >-1){
			data = data.replace("Ligado", "");
			status = 1;
		}else if(data.indexOf("Desligado") >-1){
			data = data.replace("Desligado", "");
			status = 2;
		}else if(data.indexOf("cora")>-1){
			data = data.replace("cora", "");
			status = 3;
		}else{
			data = data.replace("temperatura", "");
			//status = 2;
		}


		if(status==1 || status==2){
			var texto = $('#'+data).text();
			if(data == "resetando"){
		    		$('.btn').attr("disabled", true);
		    		$('#statusenergiaarduino').text('Sincronizando');
		    		//alert("#statusenergiaarduino");

		    }else if(data == "voltei"){
		    		$('.btn').attr("disabled", false);
		    		$('#statusenergiaarduino').text('Arduino Conectado');
		    }
			else if(status == 2){
				    texto = texto.replace("Ligada", "Desligada");
				    $('#'+data).text(texto);
				    $('#'+data).removeClass("btn-success");

		    }else if(status == 1){
		    		texto = texto.replace("Desligada", "Ligada");
				    $('#'+data).text(texto);
					$('#'+data).addClass("btn-success");
		    }
		}else if(status==3){
			$('.btncolor').each(function(){
				var esse = $(this);
				var cor = esse.data('color');

				if(cor==data){
					$('.btncolor').removeClass("active");
					esse.addClass("active")
				}
			})
		}else{
			var temp = parseInt(data);
			$('.progress-bar span').html(parseFloat(data).toFixed(1)+"º C");
			$('.progress-bar').removeClass('progress-bar-danger progress-bar-warning progress-bar-success');
			if(temp>=50){
				$('.progress-bar').addClass('progress-bar-danger');
			}
			if(temp>30 && temp<50){
				$('.progress-bar').addClass('progress-bar-warning');
			}
			if(temp<30){
				$('.progress-bar').addClass('progress-bar-success');
			}
			$('.progress-bar').css('width',temp+"%")
		}
	    




	})


	//io.emit('rotapadrao2') 
})
  
