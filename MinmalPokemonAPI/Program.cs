var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

// Initial list of Pokemon Objects
var pokemon_list = new List<Pokemon> {

    new Pokemon { Id = 1,   Name = "Bulbasaur", OwnerName = "Player1"},
    new Pokemon { Id = 2,   Name = "IvySaur",   OwnerName = "Player1"},
    new Pokemon { Id = 3,   Name = "Venasuar",  OwnerName = "Player1"},
    new Pokemon { Id = 148, Name = "Dragonair", OwnerName = "Player2"},
    new Pokemon { Id = 149, Name = "Dragonite", OwnerName = "Player2"},
    new Pokemon { Id = 150, Name = "Mewtwo",    OwnerName = "Player2"}
};

// HTTP GET Request Handler function
// With this path, return all pokemon
app.MapGet("/pokemon", () =>
{
    // Return the entire pokemon list (200 Status)
    return pokemon_list;
});

// HTTP GET Request Handler function
// With this path, return the pokemon at the given index value
app.MapGet("/pokemon/{id}", (int id) =>
{
    // Search in pokemon_list for an object based on the given id value
    var pokemon_found_by_id = pokemon_list.Find(current_pokemon => current_pokemon.Id == id);

    // If the pokemon is null, return 404
    if (pokemon_found_by_id is null)
    {
        return Results.NotFound("Pokemon ID Not Yet Supported");
    }

    // Otherwise, return the found pokemon (200 Status)
    return Results.Ok(pokemon_found_by_id);
});

// HTTP POST request handler function 
// A function to add a new pokemon to the pokemon_list
app.MapPost("/pokemon", (Pokemon pokemon_to_add) =>
{
    // Simply add the given pokemon to the list 
    pokemon_list.Add(pokemon_to_add);
    // Return the entire list (200 Status)
    return pokemon_list;
});

// HTTP PUT request handler (?)
// A function to update a pokemon based on the updated pokemon's Id value
app.MapPut("/pokemon/{id}", (Pokemon updatedPokemon) =>
{
    // Search in pokemon_list for a pokemon object based on the given pokemon (updatedPokemon)'s Id value
    var pokemon_found_by_id = pokemon_list.Find(current_pokemon => current_pokemon.Id == updatedPokemon.Id);

    // If the pokemon is null return 404
    if (pokemon_found_by_id is null)
    {
        return Results.NotFound("Pokemon ID Not Yet Supported");
    }

    // Otherwise, update the Name and OwnerName fields with the given pokemon's data (updatedPokemon)
    pokemon_found_by_id.Name = updatedPokemon.Name;
    pokemon_found_by_id.OwnerName = updatedPokemon.OwnerName;

    // Return the updated pokemon (200 Status)
    return Results.Ok(pokemon_found_by_id);
});

// HTTP DELETE Request Handler
// Deletes a pokemon from the pokemon_list given an Id number
app.MapDelete("/pokemon/{id}", (int id) =>
{
    // Search in pokemon_list for a pokemon object based on the given Id value
    var pokemon_found_by_id = pokemon_list.Find(current_pokemon => current_pokemon.Id == id);

    // If the pokemon is null, return 404
    if (pokemon_found_by_id is null)
    {
        return Results.NotFound("Pokemon ID Not Found");
    }

    // Otherwise, remove the found pokemon object from the list
    pokemon_list.Remove(pokemon_found_by_id);

    /// Return the updated pokemon list (200 Status)
    return Results.Ok(pokemon_list);
});

app.Run();


// Simple Pokemon class 
class Pokemon
{
    public int Id { get; set; }
    public required string Name { get; set; }
    public required string OwnerName { get; set; }
}