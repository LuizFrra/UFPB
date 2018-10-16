using MySql.Data.MySqlClient;
using System.Collections.Generic;
using Microsoft.Extensions.Configuration;
using Microsoft.AspNetCore.Session;
using System.Security.Claims;
using System.Data;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using BancoDeDados.Models;
using System;

namespace BancoDeDados.Services.DataBase
{
    public class DataBase : IDataBase
    {

        private readonly string connectionString;

        public DataBase(IConfiguration configuration)
        {
            connectionString = configuration.GetConnectionString("DefaultConnection");
        }
        
        public List<Dictionary<string, string>> SearchFor(string userName)
        {
            List<Dictionary<string,string>> listaData = new List<Dictionary<string,string>>();

            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();

                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = "SELECT Nome, City, ImagePath FROM Users WHERE Nome = @userName";
                    command.Parameters.AddWithValue("userName", userName);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        while(reader.Read())
                        {
                            Dictionary<string,string> data   = new Dictionary<string, string>();

                            data.Add("Nome", reader.GetString("Nome"));
                            
                            if(reader.IsDBNull(1))
                                data.Add("Cidade", "A Definir");
                            else
                                data.Add("Cidade", reader.GetString("City"));

                            if(reader.IsDBNull(2))
                                data.Add("ImagePath", "A Definir");
                            else
                                data.Add("ImagePath", reader.GetString("ImagePath"));

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
    }
}