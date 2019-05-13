#region Using
using MySql.Data.MySqlClient;
using System.Collections.Generic;
using Microsoft.Extensions.Configuration;
using System.Security.Claims;
using System.Data;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Http;
using BancoDeDados.Models;
using System;
using System.Linq;
using System.IO;
#endregion

namespace BancoDeDados.Services.DataBase
{
    public class DataBase : IDataBase
    {

        private readonly string connectionString;

        public DataBase(IConfiguration configuration)
        {
            connectionString = configuration.GetConnectionString("DefaultConnection");
        }
        
        #region Função utilizada para pegar as respostas de um comentario
        public RespostasView GetAnswer(string myID,string commentID)
        {
            RespostasView answers = new RespostasView();
            answers.comentarioID = commentID;
            answers.myID = myID;

            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT x.RespostaID, x.UserID, Users.Nome, Users.ImagePath, x.Texto, MuralUsers.UserID as MUserID, 
                    Publicacao.UserID as PUserID, Comentario.UserID as CUserID, Relacionamento.Status FROM MuralUsers, Users, Publicacao, Comentario, 
                    Respostas as x LEFT JOIN Relacionamento ON (Relacionamento.UserID1 = @myID && Relacionamento.UserID2 = x.UserID)
                    WHERE Comentario.PublicacaoID = Publicacao.PublicacaoID && Comentario.ComentarioID = @commentID && 
                    x.ComentarioID = Comentario.ComentarioID && Users.UserID = x.UserID && MuralUsers.PublicacaoID = Publicacao.PublicacaoID;";
                    
                    command.Parameters.AddWithValue("commentID", commentID);
                    command.Parameters.AddWithValue("myID", myID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        reader.Read();
                        answers.MuralUserIDPost = reader.GetString("MUserID");
                        answers.AuthorIDPost = reader.GetString("PUserID");
                        answers.AuthorIDCommnet = reader.GetString("CUserID");
                        
                        do
                        {
                            Respostas respostas = new Respostas();
                            
                            respostas.UserID = reader.GetString("UserID");
                            respostas.UserName = reader.GetString("Nome");
                            respostas.UserImage = reader.GetString("ImagePath");
                            respostas.Texto = reader.GetString("Texto");
                            respostas.RespostaID = reader.GetString("RespostaID");

                            if(reader.IsDBNull(8))
                                respostas.Status = null;
                            else
                                respostas.Status = reader.GetString("Status");

                            answers.respostas.Add(respostas);
                        }while(reader.Read());
                        
                        connection.Close();
                        return answers;
                    }
                }
                answers.respostas = null;
                connection.Close();
                return answers;
            }
        }
        #endregion
        
        #region Função utilizada para responder um comentário
        public bool DoAnswer(string userID, string commentID, string texto)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"INSERT INTO Respostas(UserID, ComentarioID, Texto) VALUES (@userID, @commentID, @texto)";
                    command.Parameters.AddWithValue("userID", userID);
                    command.Parameters.AddWithValue("commentID", commentID);
                    command.Parameters.AddWithValue("texto", texto);

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 1)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion
        
        #region Função utilizada para pegar os comentário em um post
        public CommentsView GetComments(string myID, string postID)
        {
            CommentsView comments = new CommentsView();
            comments.PublicacaoID = postID;

            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT x.ComentarioID, x.UserID, Users.Nome, Users.ImagePath, x.Texto, Publicacao.UserID as PUserID, 
                    MuralUsers.UserID as MUserID, Relacionamento.Status FROM Users, Publicacao, MuralUsers, Comentario as x LEFT JOIN 
                    Relacionamento ON (Relacionamento.UserID1 = @myID && Relacionamento.UserID2 = x.UserID) WHERE 
                    x.PublicacaoID = @postID && MuralUsers.PublicacaoID = @postID && Users.UserID = x.UserID && Publicacao.PublicacaoID = @postID;";
                    
                    command.Parameters.AddWithValue("postID", postID);
                    command.Parameters.AddWithValue("myID", myID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        reader.Read();
                        comments.myID = myID;
                        comments.MUserID = reader.GetString("MUserID");
                        comments.AuthorIDPublicacao = reader.GetString("PUserID");
                        
                        do
                        {
                            Comentarios comentarios = new Comentarios();
                            comentarios.ComentarioID = reader.GetString("ComentarioID");
                            comentarios.UserID = reader.GetString("UserID");
                            comentarios.UserName = reader.GetString("Nome");
                            comentarios.UserImage = reader.GetString("ImagePath");
                            comentarios.Texto = reader.GetString("Texto");
                            
                            if(reader.IsDBNull(7))
                                comentarios.Status = null;
                            else
                                comentarios.Status = reader.GetString("Status");

                            comments.comentarios.Add(comentarios);
                        }while(reader.Read());
                        
                        connection.Close();
                        return comments;
                    }

                }
                comments.comentarios = null;
                connection.Close();
                return comments;
            }
        }
        #endregion 
        
        #region Função utilizada para realizar um comentário
        public bool DoComment(string userID, string postID, string text)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = "INSERT INTO Comentario(UserID, PublicacaoID, Texto ) VALUES (@userID, @postID, @text)";
                    command.Parameters.AddWithValue("userID", userID);
                    command.Parameters.AddWithValue("postID", postID);
                    command.Parameters.AddWithValue("text", text);

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 1)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion
        
        #region Função utilizada para pegar os posts de amigo e exibir na pagina inicial
        public List<Posts> GetPostsFriends(string myID)
        {
            List<Posts> posts = new List<Posts>();

            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();

                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT Publicacao.UserID, Nome, ImagePath, Publicacao.PublicacaoID, Imagem, Texto  
                    FROM Publicacao, Users, Relacionamento, MuralUsers 
                    WHERE MuralUsers.UserID != @myID && Publicacao.UserID != @myID && Publicacao.UserID = Users.UserID && Relacionamento.UserID1 = @myID 
                    && Relacionamento.UserID2 = Users.UserID && Relacionamento.Status = 3 && MuralUsers.PublicacaoID = Publicacao.PublicacaoID
                    && MuralUsers.UserID =  Publicacao.UserID";

                    command.Parameters.AddWithValue("myID", myID);

                    MySqlDataReader reader = command.ExecuteReader();
                    if(reader.HasRows)
                    {
                        while(reader.Read())
                        {
                            
                            Posts data = new Posts();

                            data.UserID = reader.GetString("UserID");
                            data.PublicacaoID = reader.GetString("PublicacaoID");
                            data.UserName = reader.GetString("Nome");
                            data.UserImage = reader.GetString("ImagePath");
                            
                            if(!reader.IsDBNull(4))
                                data.ImagePath = reader.GetString("Imagem");
                            
                            if(!reader.IsDBNull(5))
                                data.Texto = reader.GetString("Texto");

                            posts.Add(data);
                        }
                        
                        connection.Close();
                        var sort = from r in posts orderby Guid.NewGuid() ascending select r;
                        posts = sort.ToList();
                        return posts;
                    }
                }
                connection.Close();
                return null;
            }

        }
        #endregion
        
        #region Função utilizada para realizar um Post
        public bool DoPost(string myID, string userID,string post, IFormFile image)
        {

            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();

                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = "INSERT INTO Publicacao (UserID, Imagem, Texto) VALUES (@myID, @Imagem, @Texto); SELECT LAST_INSERT_ID()";
                    
                    command.Parameters.AddWithValue("myID", myID);

                    //if(!string.IsNullOrEmpty(post))
                    command.Parameters.AddWithValue("Texto", post);
                    
                    if(image != null)
                    {
                        
                        string fileName = DateTime.Now.ToString("yyyymmddMMsss") + "_" + userID + Path.GetExtension(image.FileName);
                        FileStream stream = new FileStream("wwwroot/images/" + fileName, FileMode.Create);
                        image.CopyTo(stream);
                        command.Parameters.AddWithValue("Imagem", "~/images/" + fileName);
                    }
                    
                    int result = Convert.ToInt32(command.ExecuteScalar());
                    
                    
                    if(result > 0)
                    {
                        command.CommandText = $@"INSERT INTO MuralUsers(UserID, PublicacaoID) VALUES(@userID, @postID);";
                        command.Parameters.AddWithValue("@postID", result);
                        command.Parameters.AddWithValue("userID", userID);
                        int nRowsAffected = command.ExecuteNonQuery();

                        if(nRowsAffected == 1)
                        {
                            connection.Close();
                            return true;
                        }
                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion
        
        #region Função utilizada para buscar um usuário por ID
        public Relation SearchUserByID(string myID, string userID)
        {
            Relation data = new Relation();
            
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT Users.UserID, Users.Nome, Users.City, Users.ImagePath, Users.Visibility, Relacionamento.Status FROM Users 
                    LEFT JOIN Relacionamento ON Relacionamento.UserID1 = @myID && Relacionamento.UserID2 = @userID WHERE Users.UserID = @userID LIMIT 1";
                    command.Parameters.AddWithValue("myID", myID);
                    command.Parameters.AddWithValue("userID", userID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        reader.Read();
                        data.MuralUserID = reader.GetString("UserID");
                        data.MuralUserName = reader.GetString("Nome");
                        data.MuralUserImagePath = reader.GetString("ImagePath");
                        data.Visibility = reader.GetString("Visibility");
                        
                        if(reader.IsDBNull(5))
                            data.Status = null;
                        else
                            data.Status = reader.GetString("Status");

                        if(reader.IsDBNull(2))
                            data.MuralUserCity = "A Definir";
                        else
                            data.MuralUserCity = reader.GetString("City");

                        connection.Close();   
                        return data;
                    }
                }
                connection.Close();
                return null;
            }
        }
        #endregion
        
        #region Função utilizada para buscar um usuário pelo Nome %
        public List<Dictionary<string, string>> SearchForName(string myID, string userName)
        {
            List<Dictionary<string,string>> listaData = new List<Dictionary<string,string>>();

            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();

                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT u.UserID, u.Nome, u.City, u.ImagePath, r.Status FROM Users as u LEFT JOIN 
                    Relacionamento as r ON (r.UserID1 = @myID && r.UserID2 = u.UserID) WHERE Nome LIKE @username && UserID != @myID";
                    command.Parameters.AddWithValue("myID", myID);
                    command.Parameters.AddWithValue("userName", userName + "%");

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        while(reader.Read())
                        {
                            Dictionary<string,string> data   = new Dictionary<string, string>();

                            data.Add("UserID", reader.GetString("UserID"));
                            data.Add("Nome", reader.GetString("Nome"));
                            data.Add("ImagePath", reader.GetString("ImagePath"));
                            
                            if(reader.IsDBNull(4))
                                data.Add("Status", null);
                            else
                                data.Add("Status", reader.GetString("Status"));

                            if(reader.IsDBNull(2))
                                data.Add("Cidade", "A Definir");
                            else
                                data.Add("Cidade", reader.GetString("City"));

                            listaData.Add(data);                           
                        }

                        connection.Close();
                        return listaData;
                    }
                }

                connection.Close();
                return null;
            }           
        }
        #endregion
        
        #region Função utilizada para criar uma sessão de login
        public bool AuthenticationLogin(HttpContext context, Login data)
        {
            var user = VerifyAuth(data.Email, data.Password);
            if(user != null)
            {
                
                var claims = new List<Claim>
                {
                    new Claim("UserID", user["UserID"]),
                    new Claim("Nome", user["Nome"]),
                    new Claim(ClaimTypes.Role, "User"),
                    new Claim("ImagePath", user["ImagePath"])    
                };
                
                var claimsIdentity = new ClaimsIdentity(claims, CookieAuthenticationDefaults.AuthenticationScheme);
                
                AuthenticationHttpContextExtensions.SignInAsync(context, CookieAuthenticationDefaults.AuthenticationScheme, new ClaimsPrincipal(claimsIdentity));    

                return true;
            }
            return false;
        }
        #endregion
        
        #region Função utilizada para validar os dados de login
        public Dictionary<string,string> VerifyAuth(string email, string password)
        {
            
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT UserID, Nome, ImagePath FROM Users WHERE Email = @email && Pass = @password";

                    command.Parameters.AddWithValue("email", email);
                    command.Parameters.AddWithValue("password", password);

                    MySqlDataReader user = command.ExecuteReader();
                    
                    if(user.HasRows)
                    {   
                        user.Read();
                        
                        Dictionary<string,string> data = new Dictionary<string,string>();
                        data.Add("UserID", user.GetString(0));
                        data.Add("Nome", user.GetString(1));
                        data.Add("ImagePath", user.GetString("ImagePath"));

                        connection.Close();
                        return data;
                    }
                    
                }

                connection.Close();
                return null;
            }
            
        }
        #endregion
        
        #region Função utilizada para registrar um usuário
        public bool Register(Users user)
        {
            using (MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();

                if(connection.State == ConnectionState.Open && VerifyExistEmail(user.Email))
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = "INSERT INTO Users(Nome, Email, Pass, ImagePath) VALUES (@Name, @Email, @Pass, @ImagePath)";

                    command.Parameters.AddWithValue("Name", user.Name);
                    command.Parameters.AddWithValue("Email", user.Email);
                    command.Parameters.AddWithValue("Pass", user.Password);
                    command.Parameters.AddWithValue("ImagePath", "~/images/user.png");

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 1)
                    {
                        connection.Close();
                        return true;
                    }
                }
                
                connection.Close();
                return false;
            }
        }
        #endregion
        
        #region Função utilizada para verificar se um email já existe
        public bool VerifyExistEmail(string email)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();

                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT Email FROM Users WHERE Email = @Email LIMIT 1";
                
                    command.Parameters.AddWithValue("Email", email);
                    
                    MySqlDataReader rows = command.ExecuteReader();

                    if(rows.HasRows)
                    {
                        connection.Close();
                        return false;
                    }
                }

                connection.Close();
                return true;

            }
        }
        #endregion
        
        #region Função utilizada para o envio de amizades
        public bool SendFriend(string myID, string userID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"INSERT INTO Relacionamento VALUES(@myID, @userID, 1), (@userID, @myID, 2)";
                    command.Parameters.AddWithValue("myID", myID);
                    command.Parameters.AddWithValue("userID", userID);

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 2)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion
        
        #region Função utilizada para cancelar o envio de uma amizade
        public bool CancelFriendRequest(string myID, string userID)
        {
            using (MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"DELETE FROM Relacionamento WHERE (UserID1 = @myID && UserID2 = @userID) 
                    || ( UserID1 = @userID && UserID2 = @myID)";
                    command.Parameters.AddWithValue("userID", userID);
                    command.Parameters.AddWithValue("myID", myID);

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 2)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion

        #region Função utilizada para aceitar a solicitação de amizade
        public bool AcceptFriendRequest(string myID, string userID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"UPDATE Relacionamento SET Status = 3 WHERE (UserID1 = @myID && UserID2 = @userID) ||
                    (UserID1 = @userID && UserID2 = @myID)";
                    command.Parameters.AddWithValue("myID", myID);
                    command.Parameters.AddWithValue("userID", userID);

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 2)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion
        
        #region Função Utilizada para desfazer uma Amizade
        public bool UndoFriend(string myID, string userID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"DELETE FROM Relacionamento WHERE (UserID1 = @myID && UserID2 = @userID) 
                    || ( UserID1 = @userID && UserID2 = @myID)";
                    command.Parameters.AddWithValue("userID", userID);
                    command.Parameters.AddWithValue("myID", myID);

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 2)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion

        #region Função utilizada para bloquear um usuário
        public bool BlockUser(string myID, string userID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"DELETE Publicacao FROM Publicacao INNER JOIN MuralUsers ON 
                    (MuralUsers.PublicacaoID = Publicacao.PublicacaoID) WHERE (Publicacao.UserID = @myID AND MuralUsers.UserID = @userID) || 
                    (Publicacao.UserID = @userID AND MuralUsers.UserID = @myID)";
                    command.Parameters.AddWithValue("userID", userID);
                    command.Parameters.AddWithValue("myID", myID);
                    command.ExecuteNonQuery();

                    command.CommandText = $@"DELETE FROM Relacionamento WHERE (UserID1 = @myID && UserID2 = @userID) || (UserID1 = @userID && UserID2 = @myID)";
                    command.ExecuteNonQuery();
                    
                    command.CommandText = $@"INSERT INTO Relacionamento VALUES (@myID, @UserID, 4), (@userID, @myID, 6)";
                    int nRowsAffected = command.ExecuteNonQuery();

                    command.CommandText = $@"DELETE r FROM Respostas as r, Comentario as c WHERE r.ComentarioID = c.ComentarioID AND 
                                            (c.UserID = @myID || c.UserID = @userID) AND (r.UserID = @myID || r.UserID = @userID)";
                    command.ExecuteNonQuery();

                    if(nRowsAffected == 2)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion

        #region Função utilizada para pegar os usuário que um determinado usuário bloqueou
        public List<Relation> GetBlockUsers(string myID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@" SELECT u.Nome, u.UserID FROM Users as u INNER JOIN Relacionamento as r ON 
                    (r.UserID1 = @myID &&  r.UserID2 = u.UserID && r.Status = 4)";  
                    command.Parameters.AddWithValue("myID", myID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        List<Relation> relations = new List<Relation>();
                        while(reader.Read())
                        {
                            Relation relation = new Relation();

                            relation.MuralUserName = reader.GetString("Nome");
                            relation.MuralUserID = reader.GetString("UserID");

                            relations.Add(relation);

                        }

                        connection.Close();
                        return relations;
                    }
                }
                connection.Close();
                return null;
            }
        }
        #endregion
        
        #region Função utilizada para realizar desbloqueio de usuário
        public bool UnLockUser(string myID, string userID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"DELETE r FROM Relacionamento as r WHERE (r.UserID1 = @myID && r.UserID2 = @userID && r.Status = 4) || 
                    (r.UserID1 = @userID && r.UserID2 = @myID && r.Status = 6)";
                    command.Parameters.AddWithValue("myID", myID);
                    command.Parameters.AddWithValue("userID", userID);
                    
                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 2)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion
        
        #region Função utilizada para pegar os amigos de um usuário
        public List<Friends> GetFriends(string userID)
        {
            List<Friends> friends = new List<Friends>();
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(ConnectionState.Open == connection.State)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT Users.UserID, Users.Nome, Users.ImagePath, Users.City FROM Users, Relacionamento 
                                            WHERE Relacionamento.UserID1 = @userID && Relacionamento.UserID2 = Users.UserID && Relacionamento.Status = 3";
                    command.Parameters.AddWithValue("userID", userID);
                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        while(reader.Read())
                        {
                            Friends data = new Friends();
                            data.UserID = reader.GetString("UserID");
                            data.UserName = reader.GetString("Nome");
                            data.ImagePath = reader.GetString("ImagePath");
                            
                            if(reader.IsDBNull(3))
                                data.City = "A Definir";
                            else
                                data.City = reader.GetString("City");
                            
                            friends.Add(data);
                        }
                        connection.Close();
                        return friends;
                    }
                }
                connection.Close();
                return null;
            }
        }
        #endregion
        
        #region Função utilizada para pegar os amigos em comum

        public List<Friends> GetMutualFriends(string myID, string userID)
        {
            List<Friends> friends = new List<Friends>();
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT u.UserID, u.Nome, u.ImagePath, u.City FROM Users as u LEFT JOIN Relacionamento as ru 
                    ON (ru.UserID1 = @userID AND ru.Status = 3) LEFT JOIN Relacionamento as ru2 ON (ru2.userID1 = @myID 
                    AND ru2.userID2 = ru.UserID2 AND ru2.Status = 3) WHERE ru2.UserID2 = u.UserID";
                    command.Parameters.AddWithValue("userID", userID);
                    command.Parameters.AddWithValue("myID", myID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        while(reader.Read())
                        {
                            Friends data = new Friends();
                            data.UserID = reader.GetString("UserID");
                            data.UserName = reader.GetString("Nome");
                            data.ImagePath = reader.GetString("ImagePath");
                            
                            if(reader.IsDBNull(3))
                                data.City = "A Definir";
                            else
                                data.City = reader.GetString("City");
                            
                            friends.Add(data);
                        }
                        connection.Close();
                        return friends;
                    }
                }
                connection.Close();
                return null;
            }
        }
        

        #endregion
        
        #region Função para pegar as solicitações de amizades

        public List<Friends> GetFriendsRequests(string myID)
        {
            List<Friends> friends = new List<Friends>();
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(ConnectionState.Open == connection.State)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT u.UserID, u.Nome, u.ImagePath, u.City FROM Users as u, Relacionamento as r WHERE 
                                            r.UserID1 = @myID AND r.Status = 2 AND u.UserID = r.UserID2";
                    command.Parameters.AddWithValue("myID", myID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        while(reader.Read())
                        {
                            Friends data = new Friends();
                            data.UserID = reader.GetString("UserID");
                            data.UserName = reader.GetString("Nome");
                            data.ImagePath = reader.GetString("ImagePath");
                            
                            if(reader.IsDBNull(3))
                                data.City = "A Definir";
                            else
                                data.City = reader.GetString("City");
                            
                            friends.Add(data);
                        }
                        connection.Close();
                        return friends;
                    }
                }
                connection.Close();
                return null;
            }
        }

        #endregion

        #region Função utilizada para pegar os posts de um mural
        public List<Posts> GetPostsMural(string myID, string userID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                List<Posts> posts = new List<Posts>();
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT  Users.Nome, Users.ImagePath, x.UserID, x.PublicacaoID, x.Imagem, x.Texto, 
                    Relacionamento.Status FROM Users, MuralUsers, Publicacao as x LEFT JOIN Relacionamento ON 
                    (Relacionamento.UserID1 = @myID AND Relacionamento.UserID2 = x.UserID) WHERE MuralUsers.UserID = @userID &&  
                    MuralUsers.PublicacaoID = x.PublicacaoID AND x.UserID = Users.UserID;";

                    command.Parameters.AddWithValue("myID", myID);
                    command.Parameters.AddWithValue("userID", userID);
                    MySqlDataReader reader = command.ExecuteReader();
                    
                    if(reader.HasRows)
                    {
                        while(reader.Read())
                        {
                            Posts data = new Posts();
                            data.UserID = reader.GetString("UserID");
                            data.UserName = reader.GetString("Nome");
                            data.UserImage = reader.GetString("ImagePath");
                            data.PublicacaoID = reader.GetString("PublicacaoID");
                            
                            if(!reader.IsDBNull(5))
                                data.Texto =  reader.GetString("Texto");
                            else
                                data.Texto = null;

                            if(!reader.IsDBNull(4))
                                data.ImagePath = reader.GetString("Imagem");
                            else
                                data.ImagePath = null;

                            if(!reader.IsDBNull(6))
                                data.Status = reader.GetString("Status");
                            else
                                data.Status = null;

                            posts.Add(data);
                            
                        }
                        connection.Close();
                        var sort = from r in posts orderby Guid.NewGuid() ascending select r;
                        posts = sort.ToList();
                        return posts;
                    }
                }
                connection.Close();
                return null;
            }
            
        }
        #endregion

        #region Função utilizada para fazer alterações no perfil
        public bool ChangePerfil(string userID, IFormFile image, string visibility, string city, string pass)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT Users.Nome, Users.City, Users.Visibility, Users.Pass FROM Users WHERE UserID = @userID LIMIT 1";
                    command.Parameters.AddWithValue("userID", userID);
                    MySqlDataReader reader = command.ExecuteReader();
                    if(reader.HasRows)
                    {
                        reader.Read();

                        if(reader.GetString("Pass") == pass)
                        {
                            command.CommandText = "UPDATE Users SET Visibility = @visibility";
                        
                            if(!string.IsNullOrEmpty(city))
                            {
                                command.CommandText += ", City = @city";
                                command.Parameters.AddWithValue("city", city);
                            }
                            if(image != null)
                            {
                                string fileName = DateTime.Now.ToString("yyyymmddMMsss") + "_" + userID + Path.GetExtension(image.FileName);
                                FileStream stream = new FileStream("wwwroot/images/" + fileName, FileMode.Create);
                                image.CopyTo(stream);
                                command.CommandText += ", ImagePath = @imagem";
                                command.Parameters.AddWithValue("imagem", "~/images/" + fileName);
                            }
                            command.CommandText += " WHERE UserID = @userID";
                            command.Parameters.AddWithValue("visibility", visibility);
                            reader.Close();
                            int nRowsAffected = command.ExecuteNonQuery();

                            if(nRowsAffected == 1)
                            {
                                connection.Close();
                                return true;
                            }

                        }
                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion

        #region Função utilizada para deletar uma resposta
        public bool DeleteAnswer(string myID, string answerID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT Respostas.UserID, MuralUsers.UserID as MUser, Comentario.UserID CUser, 
                    Publicacao.UserID as PUser from Respostas, MuralUsers, Comentario, Publicacao WHERE Respostas.RespostaID = @answerID &&
                    Respostas.ComentarioID = Comentario.ComentarioID AND Comentario.PublicacaoID = Publicacao.PublicacaoID AND 
                    Publicacao.PublicacaoID = MuralUsers.PublicacaoID;";
                    command.Parameters.AddWithValue("answerID", answerID);
                    
                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        reader.Read();

                        if(myID == reader.GetString("UserID") || myID == reader.GetString("MUser") || myID == reader.GetString("CUser")
                        || myID == reader.GetString("PUser"))
                        {
                            command.CommandText = $@"DELETE FROM Respostas WHERE RespostaID = @answerID";
                            reader.Close();
                            int nRowsAffected = command.ExecuteNonQuery();

                            if(nRowsAffected == 1)
                            {
                                connection.Close();
                                return true;
                            }
                        }
                    }

                }
                connection.Close();
                return false;
            }
        }
        #endregion

        #region Função utilizada para deletar um Comentário
        public bool DeleteComment(string myID, string commentID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT Publicacao.UserID as PUserID, Comentario.UserID as CUserID ,MuralUsers.UserID as MUSerID 
                    FROM Publicacao, Comentario,  MuralUsers WHERE Comentario.ComentarioID = @commentID && Publicacao.PublicacaoID = Comentario.PublicacaoID 
                    && Comentario.PublicacaoID = MuralUsers.PublicacaoID LIMIT 1";
                    command.Parameters.AddWithValue("commentID", commentID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        reader.Read();

                        if(myID == reader.GetString("PUserID") || myID == reader.GetString("CUserID") || myID == reader.GetString("MUserID"))
                        {
                            command.CommandText = $@"DELETE FROM Comentario WHERE Comentario.ComentarioID = @commentID";
                            reader.Close();

                            int nRowsAffected = command.ExecuteNonQuery();

                            if(nRowsAffected == 1)
                            {
                                connection.Close();
                                return true;
                            }
                        }

                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion

        #region Função utilizada para deletar um Post
        public bool DeletePost(string myID, string postID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT MuralUsers.UserID as MUserID, Publicacao.UserID as PUserID FROM Publicacao, MuralUsers 
                    WHERE Publicacao.PublicacaoID = @postID AND MuralUsers.PublicacaoID = Publicacao.PublicacaoID LIMIT 1";
                    command.Parameters.AddWithValue("postID", postID);

                    MySqlDataReader reader =  command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        reader.Read();

                        if(myID == reader.GetString("MUserID") || myID == reader.GetString("PUserID"))
                        {
                            reader.Close();
                            command.CommandText = $@"DELETE FROM Publicacao WHERE Publicacao.PublicacaoID = @postID";
                            int nRowsAffected = command.ExecuteNonQuery();

                            if(nRowsAffected == 1)
                            {
                                connection.Close();
                                return true;
                            }
                        }
                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion

        #region Função utilizada na Criação de um Grupo
        public bool CreateGroup(string myID, Groups groups)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"INSERT INTO Grupo(Nome, Descricao, Foto) VALUES(@nome, @descricao, @foto); SELECT LAST_INSERT_ID()";
                    command.Parameters.AddWithValue("nome", groups.Nome);

                    if(string.IsNullOrEmpty(groups.Descricao))
                        command.Parameters.AddWithValue("descricao", "Sem Descrição");
                    else
                        command.Parameters.AddWithValue("descricao", groups.Descricao);
                    
                    if(groups.Image == null)
                        command.Parameters.AddWithValue("foto", "~/images/grupo.png");
                    else
                    {
                        string fileName = DateTime.Now.ToString("yyyymmddMMsss") + "_" + myID + Path.GetExtension(groups.Image.FileName);
                        FileStream stream = new FileStream("wwwroot/images/" + fileName, FileMode.Create);
                        groups.Image.CopyTo(stream);
                        command.Parameters.AddWithValue("foto", "~/images/" + fileName);
                    }

                    UInt64 grupoID = (UInt64)(command.ExecuteScalar());

                    if(grupoID > 0)
                    {
                        command.CommandText = $@"INSERT INTO RelacionamentoGU(GrupoID, UserID, Status) VALUES (@grupoID, @myID, 3);
                        INSERT INTO GrupoAdmin(GrupoID, UserID) VALUES (@grupoID, @myID)";
                        command.Parameters.AddWithValue("myID", myID);
                        command.Parameters.AddWithValue("grupoID", grupoID);
                        
                        int nRowsAffected = command.ExecuteNonQuery();
                        
                        if(nRowsAffected == 2)
                        {
                            connection.Close();
                            return true;
                        }
                    }
                    
                }
                connection.Close();
                return false;
            }
        }
        #endregion
        
        #region Função para pegar os grupos e Listar
        public List<Groups> GetGroups(string myID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(ConnectionState.Open == connection.State)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@" SELECT g.GrupoID, g.Nome, g.Descricao, g.Foto, relg.Status as RelGrupo FROM Grupo as g LEFT JOIN 
                    RelacionamentoGU as relg ON (relg.UserID = @myID && relg.GrupoID = g.GrupoID)";
                    command.Parameters.AddWithValue("myID", myID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        List<Groups> groups = new List<Groups>();
                        while(reader.Read())
                        {
                            Groups group =  new Groups();

                            if(reader.IsDBNull(4) || (reader.GetString("RelGrupo") != "4" && reader.GetString("RelGrupo") != "6"))
                            {
                                group.groupID = reader.GetString("GrupoID");
                                group.Nome = reader.GetString("Nome");
                                group.Descricao = reader.GetString("Descricao");
                                group.ImagePath = reader.GetString("Foto");
                                
                                if(reader.IsDBNull(4))
                                    group.Status = "0";
                                else
                                    group.Status = reader.GetString("RelGrupo");
                            }
                            groups.Add(group);  
                        }
                        connection.Close();
                        return groups;
                    }
                }
                connection.Close();
                return null;
            }
        }
        #endregion
        
        #region Função para buscar os grupos por nome %
        public List<Groups> GetGroupsByName(string myID, string name)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(ConnectionState.Open == connection.State)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@" SELECT g.GrupoID, g.Nome, g.Descricao, g.Foto, relg.Status as RelGrupo FROM Grupo as g LEFT JOIN 
                    RelacionamentoGU as relg ON (relg.UserID = @myID && relg.GrupoID = g.GrupoID) WHERE Nome LIKE @name";
                    command.Parameters.AddWithValue("myID", myID);
                    command.Parameters.AddWithValue("name", name + "%");

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        List<Groups> groups = new List<Groups>();
                        while(reader.Read())
                        {
                            Groups group =  new Groups();

                            if(reader.IsDBNull(4) || (reader.GetString("RelGrupo") != "4" && reader.GetString("RelGrupo") != "6"))
                            {
                                group.groupID = reader.GetString("GrupoID");
                                group.Nome = reader.GetString("Nome");
                                group.Descricao = reader.GetString("Descricao");
                                group.ImagePath = reader.GetString("Foto");
                                
                                if(reader.IsDBNull(4))
                                    group.Status = "0";
                                else
                                    group.Status = reader.GetString("RelGrupo");
                            }
                            groups.Add(group);  
                        }
                        connection.Close();
                        return groups;
                    }
                }
                connection.Close();
                return null;
            }
        }
        #endregion

        #region Função para se juntar a um grupo
        public bool JoinGroup(string myID, string groupID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT Visibilidade FROM Grupo WHERE GrupoID = @groupID LIMIT 1";
                    command.Parameters.AddWithValue("groupID", groupID);
                    
                    MySqlDataReader reader = command.ExecuteReader();
                    string visibilidade = "";

                    if(reader.HasRows)
                    {
                        reader.Read();
                        visibilidade = reader.GetString("Visibilidade");
                    }
                    
                    if(visibilidade == "0")
                        command.CommandText = $@"INSERT INTO RelacionamentoGU(GrupoID, UserID, Status) VALUES (@groupID, @myID, 2)";
                    else
                        command.CommandText = $@"INSERT INTO RelacionamentoGU(GrupoID, UserID, Status) VALUES (@groupID, @myID, 1)";
                    
                    command.Parameters.AddWithValue("myID", myID);
                    reader.Close();

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 1)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
                return false;
            }   
        }
        #endregion
        
        #region Função Utilizada para abandonar status de admin

        public bool LetBeAdmin(string myID, string groupID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT count(UserID) as NAdmins FROM RelacionamentoGU WHERE GrupoID = @groupID AND Status = 3";
                    command.Parameters.AddWithValue("groupID", groupID);

                    int result = Convert.ToInt32(command.ExecuteScalar());

                    if(result > 1)
                    {
                        command.CommandText = "UPDATE RelacionamentoGU SET Status = 2 WHERE GrupoID = @groupID AND UserID = @myID";
                        command.Parameters.AddWithValue("myID", myID);

                        int nRowsAffected = command.ExecuteNonQuery();
                        
                        if(nRowsAffected == 1)
                        {
                            connection.Close();
                            return true;
                        }
                    }
                    
                }
                connection.Close();
                return false;
            }
        }

        #endregion

        #region Função utilizada para remover usuario da tabela : Remover do Grupo, Excluir, recusar solicitação ...
        public bool RemoveStatusFromGroup(string myID, string groupID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"DELETE RelacionamentoGU FROM RelacionamentoGU WHERE GrupoID = @groupID && UserID = @myID";
                    command.Parameters.AddWithValue("myID", myID);
                    command.Parameters.AddWithValue("groupID", groupID);

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 1)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion
        
        #region Função utilizada para gerenciamento do grupo, retorno de usuários, posts etc...
        public ManageGroup ManageGroup(string myID, string groupID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                ManageGroup users = new ManageGroup();
                users.groupID = groupID;
                connection.Open();

                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT rgu.UserID FROM RelacionamentoGU as rgu WHERE rgu.UserID = @myID AND rgu.GrupoID = @groupID 
                                            AND rgu.Status = 3";
                    command.Parameters.AddWithValue("myID", myID);
                    command.Parameters.AddWithValue("groupID", groupID);

                    MySqlDataReader reader = command.ExecuteReader();
                    
                    if(reader.HasRows)
                    {
                        reader.Close();
                        command.CommandText = $@"SELECT rgu.Status, rgu.UserID, u.Nome, u.ImagePath, u.City FROM RelacionamentoGU as rgu 
                        LEFT JOIN Users as u ON (u.UserID = rgu.UserID) WHERE rgu.GrupoID = @groupID && rgu.UserID != @myID";

                        reader = command.ExecuteReader();

                        if(reader.HasRows)
                        {
                            while(reader.Read())
                            {
                                UsersGroups user = new UsersGroups();
                                user.UserID = reader.GetString("UserID");
                                user.UserName = reader.GetString("Nome");
                                user.ImagePath = reader.GetString("ImagePath");
                                user.Status = reader.GetString("Status");

                                if(reader.IsDBNull(4))
                                    user.City = "A Definir";
                                else
                                    user.City = reader.GetString("City");
                                
                                users.Users.Add(user);
                            }
                            connection.Close();
                            return users;
                        }
                    }
                }
                users.Users = null;
                connection.Close();
                return users;
            }
        }
        #endregion
        
        #region Função utilizada para alterar o Status do usuário na tabela
        public bool ManageUserGroup(string userID, string groupID, int status)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"UPDATE  RelacionamentoGU SET Status = @status WHERE GrupoID = @groupID AND UserID = @UserID";
                    command.Parameters.AddWithValue("UserID", userID);
                    command.Parameters.AddWithValue("groupID", groupID);
                    command.Parameters.AddWithValue("status", status);
                    
                    int nRowsAffected = command.ExecuteNonQuery();

                    if(status == 4)
                    {
                        command.CommandText = $@"DELETE p FROM MuralGrupo as g, Publicacao as p WHERE g.GrupoID = @groupID AND
                                                g.PublicacaoID = p.PublicacaoID AND p.UserID = @UserID";
                        command.ExecuteNonQuery();
                    }

                    if(nRowsAffected == 1)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
            return false;
            }
        }
        #endregion
        
        #region Função utilizada para fazer alterações na configuração de um grupo
        public bool ChangeGroup(string myID, Groups group)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT rgu.UserID FROM RelacionamentoGU as rgu WHERE rgu.UserID = @myID && rgu.GrupoID = @grupoID && Status = 3 LIMIT 1";
                    command.Parameters.AddWithValue("myID", myID);
                    command.Parameters.AddWithValue("grupoID", group.groupID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        reader.Close();
                        command.CommandText = $@"UPDATE Grupo SET Visibilidade = @visibilidade";
                        command.Parameters.AddWithValue("visibilidade", group.Visibility);
                        
                        if(!string.IsNullOrEmpty(group.Descricao))
                        {
                            command.CommandText += ", Descricao = @descricao";
                            command.Parameters.AddWithValue("descricao", group.Descricao);
                        }

                        if(!string.IsNullOrEmpty(group.Nome))
                        {
                            command.CommandText += ", Nome = @nome";
                            command.Parameters.AddWithValue("nome", group.Nome);
                        }

                        if(group.Image != null)
                        {
                            string fileName = DateTime.Now.ToString("yyyymmddMMsss") + "_" + myID + Path.GetExtension(group.Image.FileName);
                            FileStream stream = new FileStream("wwwroot/images/" + fileName, FileMode.Create);
                            group.Image.CopyTo(stream);
                            command.CommandText += ", Foto = @foto";
                            command.Parameters.AddWithValue("foto", "~/images/" + fileName);      
                        }
                        
                        command.CommandText += " WHERE GrupoID = @grupoID";

                        int nRowsAffected = command.ExecuteNonQuery();

                        if(nRowsAffected == 1)
                        {
                            connection.Close();
                            return false;
                        }

                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion
    
        #region Função que retorna os grupos em que um usuário está
        public List<Groups> GetUserGroups(string myID, string userID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                List<Groups> groups = new List<Groups>();

                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT rgu.GrupoID, g.Nome, g.Descricao, g.Foto, rgu2.Status FROM Grupo as g, RelacionamentoGU as rgu 
                    JOIN RelacionamentoGU as rgu2 ON (rgu2.UserID = @myID AND rgu.GrupoID = rgu2.GrupoID) WHERE rgu.UserID = @userID AND 
                    (rgu.Status = 3 || rgu.Status = 2) AND g.GrupoID = rgu.GrupoID";
                    command.Parameters.AddWithValue("myID", myID);
                    command.Parameters.AddWithValue("userID", userID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        while(reader.Read())
                        {
                            Groups group = new Groups();
                            group.groupID = reader.GetString("GrupoID");
                            group.Nome = reader.GetString("Nome");
                            group.Descricao = reader.GetString("Descricao");
                            group.ImagePath = reader.GetString("Foto");
                            
                            if(!reader.IsDBNull(4))
                                group.Status = reader.GetString("Status");
                            else
                                group.Status = null;
                            groups.Add(group);
                        }
                        connection.Close();
                        return groups;
                    }
                }
                connection.Close();
                return null;
            }
        }
        #endregion

        #region Função Utilizada para Excluir um grupo
        public bool DeleteGroup(string userID, string groupID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT UserID FROM RelacionamentoGU WHERE GrupoID = @grupoID AND UserID = @userID AND Status = 3 LIMIT 1";
                    command.Parameters.AddWithValue("userID", userID);
                    command.Parameters.AddWithValue("grupoID", groupID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        reader.Close();
                        command.CommandText = "DELETE Grupo FROM Grupo WHERE GrupoID = @grupoID";
                        int nRowsAffected = command.ExecuteNonQuery();

                        if(nRowsAffected == 1)
                        {
                            connection.Close();
                            return true;
                        } 
                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion

        #region Função Utilizada para fazer postagem no grupo

        public bool DoPostGroup(string myID, string groupID, string post, IFormFile image)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();

                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = "INSERT INTO Publicacao (UserID, Imagem, Texto) VALUES (@myID, @Imagem, @Texto); SELECT LAST_INSERT_ID()";
                    
                    command.Parameters.AddWithValue("myID", myID);

                    if(!string.IsNullOrEmpty(post))
                        command.Parameters.AddWithValue("Texto", post);
                    
                    if(image != null)
                    {
                        
                        string fileName = DateTime.Now.ToString("yyyymmddMMsss") + "_" + myID + Path.GetExtension(image.FileName);
                        FileStream stream = new FileStream("wwwroot/images/" + fileName, FileMode.Create);
                        image.CopyTo(stream);
                        command.Parameters.AddWithValue("Imagem", "~/images/" + fileName);
                    }
                    
                    int result = Convert.ToInt32(command.ExecuteScalar());
                    
                    if(result > 0)
                    {
                        command.CommandText = $@"INSERT INTO MuralGrupo(GrupoID, PublicacaoID) VALUES(@groupID, @postID);";
                        command.Parameters.AddWithValue("postID", result);
                        command.Parameters.AddWithValue("groupID", groupID);
                        int nRowsAffected = command.ExecuteNonQuery();

                        if(nRowsAffected == 1)
                        {
                            connection.Close();
                            return true;
                        }
                    }
                }
                connection.Close();
                return false;
            }
        }
        #endregion
    
        #region Função Utilizada para pegar os conteúdos do grupo
        
        public GroupView GetGroupContent(string myID, string groupID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                GroupView content = new GroupView();
                content.myID = myID;
                content.groupID = groupID;
                connection.Open();
                
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT g.Nome, g.Foto, rgu.Status FROM Grupo as g,RelacionamentoGU as rgu 
                                            WHERE UserID = @myID AND rgu.GrupoID = @grupoID && g.GrupoID = rgu.GrupoID LIMIT 1";
                    command.Parameters.AddWithValue("grupoID", groupID);
                    command.Parameters.AddWithValue("myID", myID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        reader.Read();
                        content.staff = reader.GetString("Status");
                        content.GroupName = reader.GetString("Nome");
                        content.GroupImage = reader.GetString("Foto");
                        reader.Close();

                        command.CommandText = $@"SELECT  Users.Nome, Users.ImagePath, x.UserID, x.PublicacaoID, x.Imagem, x.Texto, 
                        Relacionamento.Status FROM Users, MuralGrupo, Publicacao as x LEFT JOIN Relacionamento ON 
                        (Relacionamento.UserID1 = @myID AND Relacionamento.UserID2 = x.UserID) WHERE MuralGrupo.GrupoID = @grupoID &&  
                        MuralGrupo.PublicacaoID = x.PublicacaoID AND x.UserID = Users.UserID";
                        reader = command.ExecuteReader();

                        if(reader.HasRows)
                        {
                            while(reader.Read())
                            {
                                Posts data = new Posts();
                                data.UserID = reader.GetString("UserID");
                                data.UserName = reader.GetString("Nome");
                                data.UserImage = reader.GetString("ImagePath");
                                data.PublicacaoID = reader.GetString("PublicacaoID");
                                
                                if(!reader.IsDBNull(5))
                                    data.Texto =  reader.GetString("Texto");
                                else
                                    data.Texto = null;

                                if(!reader.IsDBNull(4))
                                    data.ImagePath = reader.GetString("Imagem");
                                else
                                    data.ImagePath = null;

                                if(!reader.IsDBNull(6))
                                    data.Status = reader.GetString("Status");
                                else
                                    data.Status = null;

                                content.posts.Add(data);

                            }

                            reader.Close();
                            connection.Close();
                            var sort = from r in content.posts orderby Guid.NewGuid() ascending select r;
                            content.posts = sort.ToList();
                            return content;
                        }
                    }
                }
                content.posts = null;
                return content;
            }
        }
        
        #endregion

        #region Função Utilizada para apagar um post no grupo
        
        public bool DeletePostGroup(string postID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"DELETE FROM Publicacao WHERE Publicacao.PublicacaoID = @postID";
                    command.Parameters.AddWithValue("postID", postID);

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 1)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
                return false;
            }
        }

        #endregion

        #region Função Utilizada para pegar grupos em comum

        public List<Groups> GetMutualGroups(string myID, string userID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(ConnectionState.Open == connection.State)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT g.GrupoID, g.Nome, g.Descricao, g.Foto, rgu2.Status as RelGrupo FROM Grupo as g 
                    LEFT JOIN RelacionamentoGU as rgu ON (rgu.UserID = @userID AND (rgu.Status = 2 || rgu.Status = 3)) 
                    LEFT JOIN RelacionamentoGU as rgu2 ON (rgu2.UserID = @myID AND (rgu2.Status = 3 || rgu2.Status = 2) AND rgu.GrupoID = rgu2.GrupoID) 
                    WHERE g.GrupoID = rgu2.GrupoID;
";                  command.Parameters.AddWithValue("userID", userID);
                    command.Parameters.AddWithValue("myID", myID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        List<Groups> groups = new List<Groups>();
                        while(reader.Read())
                        {
                            Groups group =  new Groups();

                            if(reader.IsDBNull(4) || (reader.GetString("RelGrupo") != "4" && reader.GetString("RelGrupo") != "6"))
                            {
                                group.groupID = reader.GetString("GrupoID");
                                group.Nome = reader.GetString("Nome");
                                group.Descricao = reader.GetString("Descricao");
                                group.ImagePath = reader.GetString("Foto");
                                
                                if(reader.IsDBNull(4))
                                    group.Status = "0";
                                else
                                    group.Status = reader.GetString("RelGrupo");
                            }
                            groups.Add(group);  
                        }
                        connection.Close();
                        return groups;
                    }
                }
                connection.Close();
                return null;
            }
        }

        #endregion
    
        #region Função Para Pegar Comentarios de Posts em grupos

        public CommentsView GetCommentsGroups(string myID, string postID)
        {
            CommentsView comments = new CommentsView();
            comments.PublicacaoID = postID;

            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT x.ComentarioID, x.UserID, Users.Nome, Users.ImagePath, x.Texto, Publicacao.UserID as PUserID, 
                    MuralGrupo.GrupoID as MuserID, Relacionamento.Status FROM Users, Publicacao, MuralGrupo, Comentario as x LEFT JOIN 
                    Relacionamento ON (Relacionamento.UserID1 = @myID && Relacionamento.UserID2 = x.UserID) WHERE 
                    x.PublicacaoID = @postID && MuralGrupo.PublicacaoID = @postID && Users.UserID = x.UserID && Publicacao.PublicacaoID = @postID;";
                    
                    command.Parameters.AddWithValue("postID", postID);
                    command.Parameters.AddWithValue("myID", myID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        reader.Read();
                        comments.myID = myID;
                        comments.MUserID = reader.GetString("MUserID");
                        comments.AuthorIDPublicacao = reader.GetString("PUserID");
                        
                        do
                        {
                            Comentarios comentarios = new Comentarios();
                            comentarios.ComentarioID = reader.GetString("ComentarioID");
                            comentarios.UserID = reader.GetString("UserID");
                            comentarios.UserName = reader.GetString("Nome");
                            comentarios.UserImage = reader.GetString("ImagePath");
                            comentarios.Texto = reader.GetString("Texto");
                            
                            if(reader.IsDBNull(7))
                                comentarios.Status = null;
                            else
                                comentarios.Status = reader.GetString("Status");

                            comments.comentarios.Add(comentarios);
                        }while(reader.Read());
                        
                        connection.Close();
                        return comments;
                    }

                }
                comments.comentarios = null;
                connection.Close();
                return comments;
            }
        }

        #endregion

        #region Função utilizada para pegar as respostas em grupos
        public RespostasView GetAnswerGroups(string myID,string commentID)
        {
            RespostasView answers = new RespostasView();
            answers.comentarioID = commentID;
            answers.myID = myID;

            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT x.RespostaID, x.UserID, Users.Nome, Users.ImagePath, x.Texto, MuralGrupo.GrupoID as MUserID, 
                    Publicacao.UserID as PUserID, Comentario.UserID as CUserID, Relacionamento.Status FROM MuralGrupo, Users, Publicacao, Comentario, 
                    Respostas as x LEFT JOIN Relacionamento ON (Relacionamento.UserID1 = @myID && Relacionamento.UserID2 = x.UserID)
                    WHERE Comentario.PublicacaoID = Publicacao.PublicacaoID && Comentario.ComentarioID = @commentID && 
                    x.ComentarioID = Comentario.ComentarioID && Users.UserID = x.UserID && MuralGrupo.PublicacaoID = Publicacao.PublicacaoID;";
                    
                    command.Parameters.AddWithValue("commentID", commentID);
                    command.Parameters.AddWithValue("myID", myID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        reader.Read();
                        answers.MuralUserIDPost = reader.GetString("MUserID");
                        answers.AuthorIDPost = reader.GetString("PUserID");
                        answers.AuthorIDCommnet = reader.GetString("CUserID");
                        
                        do
                        {
                            Respostas respostas = new Respostas();
                            
                            respostas.UserID = reader.GetString("UserID");
                            respostas.UserName = reader.GetString("Nome");
                            respostas.UserImage = reader.GetString("ImagePath");
                            respostas.Texto = reader.GetString("Texto");
                            respostas.RespostaID = reader.GetString("RespostaID");

                            if(reader.IsDBNull(8))
                                respostas.Status = null;
                            else
                                respostas.Status = reader.GetString("Status");

                            answers.respostas.Add(respostas);
                        }while(reader.Read());
                        
                        connection.Close();
                        return answers;
                    }
                }
                answers.respostas = null;
                connection.Close();
                return answers;
            }
        }
        #endregion

        #region Função Utilizada para pegar Comentarios em grupos

        public RespostasView GetAnswerGrupo(string myID,string commentID)
        {
            RespostasView answers = new RespostasView();
            answers.comentarioID = commentID;
            answers.myID = myID;

            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT x.RespostaID, x.UserID, Users.Nome, Users.ImagePath, x.Texto, MuralGrupo.GrupoID as MUserID, 
                    Publicacao.UserID as PUserID, Comentario.UserID as CUserID, Relacionamento.Status FROM MuralGrupo, Users, Publicacao, Comentario, 
                    Respostas as x LEFT JOIN Relacionamento ON (Relacionamento.UserID1 = @myID && Relacionamento.UserID2 = x.UserID)
                    WHERE Comentario.PublicacaoID = Publicacao.PublicacaoID && Comentario.ComentarioID = @commentID && 
                    x.ComentarioID = Comentario.ComentarioID && Users.UserID = x.UserID && MuralGrupo.PublicacaoID = Publicacao.PublicacaoID;";
                    
                    command.Parameters.AddWithValue("commentID", commentID);
                    command.Parameters.AddWithValue("myID", myID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        reader.Read();
                        answers.MuralUserIDPost = reader.GetString("MUserID");
                        answers.AuthorIDPost = reader.GetString("PUserID");
                        answers.AuthorIDCommnet = reader.GetString("CUserID");
                        
                        do
                        {
                            Respostas respostas = new Respostas();
                            
                            respostas.UserID = reader.GetString("UserID");
                            respostas.UserName = reader.GetString("Nome");
                            respostas.UserImage = reader.GetString("ImagePath");
                            respostas.Texto = reader.GetString("Texto");
                            respostas.RespostaID = reader.GetString("RespostaID");

                            if(reader.IsDBNull(8))
                                respostas.Status = null;
                            else
                                respostas.Status = reader.GetString("Status");

                            answers.respostas.Add(respostas);
                        }while(reader.Read());
                        
                        connection.Close();
                        return answers;
                    }
                }
                answers.respostas = null;
                connection.Close();
                return answers;
            }
        }

        #endregion

        #region Função Utilizada para apagar Comentario grupos
        public bool DeleteCommentGroup(string postID, string commentID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT Publicacao.UserID as PUserID, Comentario.UserID as CUserID ,MuralGrupo.GrupoID as MUSerID 
                    FROM Publicacao, Comentario,  MuralGrupo WHERE Comentario.ComentarioID = @commentID && Publicacao.PublicacaoID = Comentario.PublicacaoID 
                    && Comentario.PublicacaoID = MuralGrupo.PublicacaoID LIMIT 1";
                    command.Parameters.AddWithValue("commentID", commentID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        reader.Read();
                        
                            command.CommandText = $@"DELETE FROM Comentario WHERE Comentario.ComentarioID = @commentID";
                            reader.Close();

                            int nRowsAffected = command.ExecuteNonQuery();

                            if(nRowsAffected == 1)
                            {
                                connection.Close();
                                return true;
                            }
                        

                    }
                }
                connection.Close();
                return false;
            }
        }

        #endregion

        #region Função Utilizada para apagar respostas em grupos
        public bool DeleteAnswerGroup(string myID, string answerID)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT Respostas.UserID, MuralGrupo.GrupoID as MUser, Comentario.UserID CUser, 
                    Publicacao.UserID as PUser from Respostas, MuralGrupo, Comentario, Publicacao WHERE Respostas.RespostaID = @answerID &&
                    Respostas.ComentarioID = Comentario.ComentarioID AND Comentario.PublicacaoID = Publicacao.PublicacaoID AND 
                    Publicacao.PublicacaoID = MuralGrupo.PublicacaoID;";
                    command.Parameters.AddWithValue("answerID", answerID);
                    
                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        reader.Read();

                        if(myID == reader.GetString("UserID") || myID == reader.GetString("MUser") || myID == reader.GetString("CUser")
                        || myID == reader.GetString("PUser"))
                        {
                            command.CommandText = $@"DELETE FROM Respostas WHERE RespostaID = @answerID";
                            reader.Close();
                            int nRowsAffected = command.ExecuteNonQuery();

                            if(nRowsAffected == 1)
                            {
                                connection.Close();
                                return true;
                            }
                        }
                    }

                }
                connection.Close();
                return false;
            }
        }
    }
    #endregion
}