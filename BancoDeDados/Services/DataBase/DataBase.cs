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

namespace BancoDeDados.Services.DataBase
{
    public class DataBase : IDataBase
    {

        private readonly string connectionString;

        public DataBase(IConfiguration configuration)
        {
            connectionString = configuration.GetConnectionString("DefaultConnection");
        }
        
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

                    if(!string.IsNullOrEmpty(post))
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

        public List<Dictionary<string, string>> SearchForName(string userName)
        {
            List<Dictionary<string,string>> listaData = new List<Dictionary<string,string>>();

            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();

                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = "SELECT UserID, Nome, City, ImagePath FROM Users WHERE Nome LIKE @userName";
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
    }
}