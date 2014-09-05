function socket(app){
	
	var browser = app.io.of('/browsers').on('connection',function(socket){
		socket.on('rotapadrao', function(req) {
			var led = req.led;
			app.io.broadcast(led);
			console.log('enviei ao arduino');
		})
	})

	app.io.on('connection',function(socket){
		console.log('arduino conectou');
		socket.on('message',function(data){
			console.log('arduino falando');
			console.log(data);
			browser.emit('rotaenviousuario',{
				led:data
	    		})
		})
	})

}

module.exports = socket;
