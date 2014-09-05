var express = require('express.io')
,	app = express()
,	mongoClient = require('mongodb').MongoClient
,	socket = require('./socketio')

app.http().io();

mongoClient.connect('mongodb://127.0.0.1:27017/aplicacao', function(err, db) {
	var Usuario = db.collection('usuario');
	Usuario.find({login:'admin',senha:'123'}).toArray(function(err,resp){
		console.log(resp);
		var idasereditado = resp[0]._id;
		socket(app,db,idasereditado);
	})
	

});

app.listen(8087);
