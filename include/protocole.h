//							requete					reponse				actions/explications

#define LOGIN#user#password //login,password			oui ou non			verification de l'existence
							//de l'employe								et du mdp de l'employé

#define LOGOUT  //		

#define GET_AUTHORS //								liste des auteurs	recup des auteurs en BD

#define GET_SUBJECTS //								liste des sujets	recup des sujets en BD

#define ADD_AUTHORS //		lastname,firstname		id de l'auteur		ajoute un nouvel auteur en BD

#define ADD_SUBJECT //		name 					id du sujet 		ajoute nouveau sujet dans la BD

#define ADD_BOOK //			authorId, subjectId,	id du livre			ajoute un nouveau livre dans la BD
					 	//title, isbn, pageCount, 
					 	//stockQuantity, price,
					 	// publishYear