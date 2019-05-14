using System;
using System.Collections.Generic;
using System.Data;
using Microsoft.Extensions.Configuration;
using MySql.Data.MySqlClient;

namespace Locadora.Services
{
    public class BancoDeDados : IBancoDeDados
    {
        private readonly string connectionString;

        public BancoDeDados(string ConnectionString) => connectionString = ConnectionString;

        public BancoDeDados(IConfiguration configuration)
        {
            connectionString = configuration.GetConnectionString("DefaultConnection");
        }

        public bool addCategoria(string categoria)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();

                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = @"INSERT INTO Categoria(Tipo) VALUES(@Tipo);";
                    command.Parameters.AddWithValue("Tipo", categoria);

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 1)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
            }
            return false;
        }

        public bool addClient(Cliente cliente)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();

                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = @"INSERT INTO Cliente(Nome, SobreNome, Telefone, Endereco) 
                                    VALUES(@Nome, @SobreNome, @Telefone, @Endereco);";
                    
                    command.Parameters.AddWithValue("Nome", cliente.Nome);
                    command.Parameters.AddWithValue("SobreNome", cliente.SobreNome);
                    command.Parameters.AddWithValue("Telefone", cliente.Telefone);
                    command.Parameters.AddWithValue("Endereco", cliente.Endereco);

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 1)
                    {
                        connection.Close();
                        return true;
                    }

                    connection.Close();
                }
            }
            return false;
        }

        public bool addEstrela(Estrela estrela)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();

                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = @"INSERT INTO Estrelas(IDFilme, NomeReal, NomeFicticio, DataDeNascimento) 
                        VALUES(@IDFilme, @NomeReal, @NomeFicticio, @DataDeNascimento);";
                    
                    command.Parameters.AddWithValue("IDFilme", estrela.Filme);
                    command.Parameters.AddWithValue("NomeReal", estrela.NomeReal);
                    command.Parameters.AddWithValue("NomeFicticio", estrela.NomeFicticio);
                    command.Parameters.AddWithValue("DataDeNascimento", estrela.DataDeNascimento);

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 1)
                    {
                        connection.Close();
                        return true;
                    }

                    connection.Close();
                }
            }
            return false; 
        }

        public bool addFilme(Filme filme)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();

                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = @"INSERT INTO Filme(IDCategoria, Nome) VALUES(@IDCategoria, @Nome);";
                    
                    command.Parameters.AddWithValue("IDCategoria", filme.Categoria);
                    command.Parameters.AddWithValue("Nome", filme.Nome);

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 1)
                    {
                        connection.Close();
                        return true;
                    }

                    connection.Close();
                }
            }
            return false;            
        }

        public bool addFita(int filme)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();

                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = @"INSERT INTO FITA(IDFilme) VALUES(@IDFilme);";
                    command.Parameters.AddWithValue("IDFilme", filme);

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 1)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
            }
            return false;
        }

        public bool Alugar(Alugar alugar)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();

                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = @"INSERT INTO Alugados(IDCliente, IDFita) VALUES(@IDCliente, @IDFita);";
                    command.Parameters.AddWithValue("IDCliente", alugar.Cliente);
                    command.Parameters.AddWithValue("IDFita", alugar.Fita);

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 1)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
            }
            return false;
        }

        public bool Devolver(Alugar devolver)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();

                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = @"DELETE FROM Alugados WHERE IDCliente = @IDCliente && IDFita = @IDFita;";
                    command.Parameters.AddWithValue("IDCliente", devolver.Cliente);
                    command.Parameters.AddWithValue("IDFita", devolver.Fita);

                    int nRowsAffected = command.ExecuteNonQuery();

                    if(nRowsAffected == 1)
                    {
                        connection.Close();
                        return true;
                    }
                }
                connection.Close();
            }
            return false;
        }

        public List<FilmesEmprestados> GetFitasAlugadasClientes(int cliente)
        {
            using(MySqlConnection connection = new MySqlConnection(connectionString))
            {
                connection.Open();
                
                if(connection.State == ConnectionState.Open)
                {
                    MySqlCommand command = new MySqlCommand();
                    command.Connection = connection;
                    command.CommandText = @"SELECT Nome, Tipo, IDFita FROM Categoria as C, Alugados as al, FITA AS ft 
                    JOIN Filme as fl ON fl.ID = ft.IDFilme WHERE al.IDFita = ft.ID && C.ID = fl.IDCategoria 
                    && al.IDCliente = @cliente;";
                    command.Parameters.AddWithValue("cliente", cliente);

                    MySqlDataReader reader = command.ExecuteReader();

                    if(reader.HasRows)
                    {
                        List<FilmesEmprestados> filmesEmprestados = new List<FilmesEmprestados>();

                        while(reader.Read())
                        {
                            FilmesEmprestados filme = new FilmesEmprestados();

                            filme.Categoria = reader.GetString("Tipo");
                            filme.Nome = reader.GetString("Nome");
                            filme.Fita = Convert.ToInt32(reader.GetString("IDFita"));

                            filmesEmprestados.Add(filme);
                        }

                        connection.Close();
                        return filmesEmprestados;
                    }

                }
            }
            return null;
        }
    }
}