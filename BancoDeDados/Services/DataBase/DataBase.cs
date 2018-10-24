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
        
        public List<Respostas> GetAnswer(string commentID)
        {
            List<Respostas> data = new List<Respostas>();

            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT Respostas.UserID, Users.Nome, Users.ImagePath ,Respostas.Texto, Respostas.ComentarioID FROM Respostas
                    , Users WHERE Respostas.ComentarioID = @commentID && Users.UserID = Respostas.UserID";
                    command.Parameters.AddWithValue("commentID", commentID);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        while(reader.Read())
                        {
                            Respostas respostas = new Respostas();
                            respostas.UserID = reader.GetString("UserID");
                            respostas.UserImage = reader.GetString("ImagePath");
                            respostas.UserName = reader.GetString("Nome");
                            respostas.ComentarioID = reader.GetString("ComentarioID");
                            respostas.Texto = reader.GetString("Texto");

                            data.Add(respostas);
                        }
                        connection.Close();
                        return data;
                    }
                }
                connection.Close();
                return null;
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

        public List<Comentarios> GetComments(string postID)
        {
            List<Comentarios> data = new List<Comentarios>();

            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = $@"SELECT Users.Nome, Users.UserID, Users.ImagePath, Comentario.ComentarioID,
                    Comentario.Texto FROM Users, Comentario WHERE @postID = Comentario.PublicacaoID
                    && Users.UserID = Comentario.UserID";
                    command.Parameters.AddWithValue("@postID", postID);
                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        while(reader.Read())
                        {
                            Comentarios comentarios = new Comentarios();
                            comentarios.UserID = reader.GetString("UserID");
                            comentarios.UserName = reader.GetString("Nome");
                            comentarios.UserImage = reader.GetString("ImagePath");

                            comentarios.ComentarioID = reader.GetString("ComentarioID");
                            comentarios.Texto = reader.GetString("Texto");

                            data.Add(comentarios);

                        }
                        connection.Close();
                        return data;
                    }

                }
                connection.Close();
                return null;
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
                    && Relacionamento.UserID2 = Users.UserID && Relacionamento.Status = 3 && MuralUsers.PublicacaoID = Publicacao.PublicacaoID";

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
                                data.Text = reader.GetString("Texto");

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
                        data.UserID = reader.GetString("UserID");
                        data.UserName = reader.GetString("Nome");
                        data.ImagePath = reader.GetString("ImagePath");
                        data.Visibility = reader.GetString("Visibility");
                        
                        if(reader.IsDBNull(5))
                            data.Status = null;
                        else
                            data.Status = reader.GetString("Status");

                        if(reader.IsDBNull(2))
                            data.City = "A Definir";
                        else
                            data.City = reader.GetString("City");

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
                    new Claim(ClaimTypes.Role, "User")    
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
                    command.CommandText = $@"SELECT UserID, Nome FROM Users WHERE Email = @email && Pass = @password";

                    command.Parameters.AddWithValue("email", email);
                    command.Parameters.AddWithValue("password", password);

                    MySqlDataReader user = command.ExecuteReader();
                    
                    if(user.HasRows)
                    {   
                        user.Read();
                        Dictionary<string,string> data = new Dictionary<string,string>();
                        data.Add("UserID", user.GetString(0));
                        data.Add("Nome", user.GetString(1));

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
                    command.CommandText = $@"SELECT Users.Nome, Users.ImagePath, MuralUsers.UserID, Publicacao.UserID AS puserID, Publicacao.PublicacaoID, 
                                            Publicacao.Imagem, Publicacao.Texto FROM Publicacao, MuralUsers, Users WHERE MuralUsers.UserID = @userID 
                                            && MuralUsers.PublicacaoID = Publicacao.PublicacaoID && Users.UserID = Publicacao.UserID";


                    command.Parameters.AddWithValue("userID", userID);
                    MySqlDataReader reader = command.ExecuteReader();
                    
                    if(reader.HasRows)
                    {
                        while(reader.Read())
                        {

                            Posts data = new Posts();
                            
                            if(myID == reader.GetString("puserID"))
                                data.UserDoPost = null;
                            else
                                data.UserDoPost = reader.GetString("puserID");

                            data.UserID = reader.GetString("UserID");
                            data.PublicacaoID = reader.GetString("PublicacaoID");
                            data.UserName = reader.GetString("Nome");
                            data.UserImage = reader.GetString("ImagePath");
                            
                            if(!reader.IsDBNull(5))
                                data.ImagePath = reader.GetString("Imagem");
                            
                            if(!reader.IsDBNull(6))
                                data.Text = reader.GetString("Texto");

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
    }
}