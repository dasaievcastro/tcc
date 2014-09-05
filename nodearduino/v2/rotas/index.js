function rotas(app, db, passport) {

	function loggedIn(req, res, next) {
    	var usuario = req.user;
	    if(usuario){
	    	next();
	    }else {
        	res.redirect('/');
      	}
  	}

	app.get('/',function(req, res){
      res.render('index/index',{title:'Bem-Vindo'});
    })

    app.post('/login', passport.authenticate('local', { 
	    successRedirect: '/dashboard',
	    failureRedirect: '/'  
	    })
    );

    app.get('*', loggedIn);

    app.get('/dashboard',function(req, res){
      res.render('dashboard/index',{title:'Painel Administrativo'});
    })


    app.get('/logout',
      function(req, res) {
        req.logout();
        res.redirect('/');
  	});

    app.get('*', function(req, res){
      res.render('404/index', 404);
    });
}

module.exports = rotas