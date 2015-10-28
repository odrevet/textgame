dofile('utils.lua')
dofile('h2g2/street.lua')

cur_funct = ''
vars = {
	serviette = false; h2g2 = false
}


function on_cmd(cmd)
	if(cmd == 'aide')then 
		print "Pas de panique"
		print "-Aide de la mini aventure H2G2 ! "
		print "Tapez regarder dans la plupart des lieux pour une description de l'endoit"
		print "servez vous des informations pour trouver les bonnes commande "
		print "Utiliser des verbes a l'infinitif(ex : allumer, prendre, aller)"
		print "Commandes globals"
		print "f : sauver vers ./panic.h2g2 et quitter"
		print "save <nom> : sauver vers <nom>.h2g2"
		print "load <nom> : charger depuis <nom>.h2g2"
		print "h2g2 : lire une entree dans le guide (une fois celui-ci en votre possesion). Si aucun nom entre, le menu principale du guide est affiche"
		return 'was_cmd'
	end

	if(cmd == '42')then 
		print "answer to life, the universe, and everything"
		return 'was_cmd'
	end
	
	if(cmd == 'f')then 
		return 'quit'
	end

	if(cmd == 'panic')then 
		print "DONT PANIC"
		return 'was_cmd'
	end
	
	if(cmd == 'save')then 
		vars.location = cur_funct;
		table.save(vars, 'h2g2_v3.state')
		print "game saved"
		return 'was_cmd'
	end
	
	if(cmd == 'load')then 
		vars = table.load('h2g2_v3.state')
		return 'new_location', vars.location
	end
	
	if(cmd == 'menu')then 
		menu()
		return 'was_cmd'
	end
	
	if(cmd == 'h2g2')then 
		h2g2()
		return 'was_cmd'
	end
	
	return 'nac'
end

function menu()
	print 'Votre inventaire : '
	for key,value in pairs(vars) do
		if(type(value) == 'boolean')then
			if(value == true)then
				print (key)
			end
		else
			print(key..": "..tostring(value))
		end
	end
	print '------------------------'
	
end

function h2g2(entry)
	print '		-- PAS DE PANIQUE -- 	';
	io.write 'Connexion au reseau sub-etha';
	io.write '.' 
	io.write '.' 
	io.write '.' 
	io.write '.' 
	print "connecte. "
	
	repeat
		io.write 'Quel entre voulez vous consulter (q pour quitter) ? >';
		entry = io.read()
		if(entry ~= 'q')then
			print ('recherche de '..entry..'.')
			io.write 'en attente de se://langalactik.h2g2.grdurs/wiki.\n' 
			
			if(entry == 'terre') then 
				print '-----------------------------------'
				print 'Globalement inofansif'
			else 
				if(entry == 'univers') then
					print '-----------------------------------'
					print "L'univers est tres tres tres grand"
					print "Quelques informations sur l'univers : "
					print "Exportations : aucune"
					print "Importations : aucune (voir exportation)"
					print "Population : 0"
				end
			end
		end
	until (entry == 'q')
end

function root()
	print ("Je suis dans mon lit, l'aube pointe a peine a travers la fenetre. at " .. cur_funct)
	return "room_dark"
end

function room_dark(cmd)
	if(cmd == 'regarder') then
		print 'je suis dans ma chambre, il y a ma lampe sur la table de chevet...'
		return "stay"
	end
	
	t = justWords(cmd)
	if(t==nil)then return "stay" end

	if( t[1] == 'allumer') then
		if(t[2] == nil) then 
			print "Allumer quoi ?"
			return "stay"
		end
		if( t[2] == 'lampe') then
			print ("Je tapotte la table de chevet, ah ! j'attrape l'interrupteur...\nLa lumiere illumine la chambre !\nJe me leve sans plus attendre. at " .. cur_funct)
			return "room_hilighted"
		else 
			print ("Je ne sais pas comment " .. cmd)

			return "stay"
		end
	end
	
	if(cmd == 'se lever') then
		print "Non, je n'ai aucune envie de me cogner dans le noir"
		return "stay"
	end
	
	return "unknow"
end 

function room_hilighted(cmd)
	if(cmd == 'regarder') then
		print "Ma chambre, avec la porte a droite, vers le couloir, et la porte a gauche, vers la salle de bain, tout ce qu'il y a de plus habituel"
		return "stay"
	end
	
	if((cmd == "aller a gauche") or (cmd == "aller salle de bain")) then
		return "room_bathroom"
	end
	
	if((cmd == "aller a droite") or (cmd == "aller couloir")) then
		if(vars.serviette == false) then
			print "J'ai comme l'impression d'oublier un objet banale mais qui me sera tres utile aujourd'hui... je ferai mieux de trouver quoi avant de sortir"
		else
			print "Me voila pret a partir !! Des aventures fantastiques vous attendent dans la prochaine version ! "
			return "street_in_front_house"
		end
		return "stay";
	end
	
	return "unknow"
end

function room_bathroom(cmd)
	print "Voici la salle de bain..."
	if(cmd == 'regarder') then
		print "La salle de bain, avec le lavabo, et la baignoire avec les serviettes qui pendent a cote. Derriere une pile de linge sale se trouve la porte vers ma chambre"
		return "stay"
	end
	
	if(cmd == 'prendre serviette') then
		if(vars.serviette == false) then
			vars.serviette = true
			print "Ca peut toujours servir..."
		else
			print "J'ai deja une serviette"
		end
		return "stay"
	end
	
	if(cmd == 'aller chambre')then
		print "Enjamber la pile de ligne sale n'etait pas facile, mais me revoila dans ma chambre"
		return "room_hilighted"
	end
	
	return "unknow"
end

