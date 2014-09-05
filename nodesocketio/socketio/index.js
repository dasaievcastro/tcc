function socket(app,db,idasereditado){

	var Usuario = db.collection('usuario');
	function hexToRgb(hex) {
	   var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
	   return result ? {
	       r: parseInt(result[1], 16),
	       g: parseInt(result[2], 16),
	       b: parseInt(result[3], 16)
	   } : null;
	}


	var contador = 0;
	
	app.io.on('connection',function(socket){
		console.log("conectou");
		
		app.io.route('statusled', function(req) {
			var led = String(req.data.led);
			app.io.broadcast(led);
		})

		app.io.route('statusBanco',function(req){
			Usuario.findOne({_id:idasereditado},function(err,res){
				if(err) throw err;
				delete res.login;
				delete res.senha;
				delete res._id;
				socket.emit('atualizarAoLigar',res)
			})
			
		})

		// app.io.route('verificarconexaocomarduino', function(req) {
		// 	app.io.broadcast(String(100));
		// })

		app.io.route('rotapadrao', function(req) {
			app.io.broadcast(String(req.data.valor));
		})
		// Usuario.update({_id:idasereditado},{$set:{salaONLigado:1}},function(err,res){
		// 	if(err) throw (err);
		// 	console.log(res);
		// 	//app.io.broadcast('rotadeescuta', data);
		// })

// //setTimeout(function(){
// 	setInterval(function(){
			
// 			socket.emit("0");
// 		},100)
// //},10000)

		socket.on('message',function(data){
			var dataorig = data;
			var status = 1;
			var atualizar = {};
			if(data.indexOf("Ligado")<0){
				status=2;
			}
			data = data.replace("Ligado","");
			data = data.replace("Desligado","");
			atualizar[data]=status;
			console.log(atualizar);
			Usuario.update({'_id':idasereditado},{$set:atualizar},function(err,res){
				if(err) throw new Error('Erro ao atualizar');
			 	console.log(res);
			 	app.io.broadcast('rotadeescuta', dataorig);
			})
			
			console.log(data);
			/*app.io.broadcast('respostaarduino',{
				led:data
	    		})*/
		})

		app.io.route('mudarrgb',function(req){
			var hex = req.data;
			var r = hexToRgb(hex).r;	
			var g = hexToRgb(hex).g;
			var b = hexToRgb(hex).b;
			console.log(r+'-'+g+'-'+b);
			app.io.broadcast('rgb-'+r+'-'+g+'-'+b+'-');
		})
	})

}

module.exports = socket;
