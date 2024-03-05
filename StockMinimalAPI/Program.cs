using FastEndpoints;
using FastEndpoints.Swagger;

var bld = WebApplication.CreateBuilder(args);
bld.Services.AddFastEndpoints()
            .SwaggerDocument();

var app = bld.Build();

app.UseFastEndpoints()
   .UseHttpsRedirection()
   .UseSwaggerGen();

app.Run();

#region Models

/// <summary>
/// A "Database" class to hold "owned" Stocks
/// </summary>
public static class OwnedStockDB
{
    /// <summary>
    /// The main "database" of owned stocks 
    /// </summary>
    public static readonly List<Stock> OwnedStockData =
    [
        new("VeeFriends", 999.99, 999.99),
        new("Meta", 498.19, 10),
        new("Lockheed Martin", 431.94, 1)
    ];
}

/// <summary>
/// A class to represent a stock
/// </summary>
/// <param name="companyName"> The name of the Company </param>
/// <param name="buyPrice"> The current sell price of the stock </param>
/// <param name="amountOfShares"> The amount of stock shares owned </param>
public record Stock(string companyName, double buyPrice, double amountOfShares);

#endregion

#region Endpoints

/// <summary>
/// FastEndpoints: This is a POST request endpoint
/// </summary>
public class CreateStockEndpoint : Endpoint<Stock, List<Stock>>
{
    public override void Configure()
    {
        // This POST functions to "Add a Stock to the OwnedStockDB List"
        Post("/api/owned-stocks");
        AllowAnonymous();
    }

    public override async Task HandleAsync(Stock req, CancellationToken ct)
    {
        OwnedStockDB.OwnedStockData.Add(req);

        await SendAsync(OwnedStockDB.OwnedStockData, cancellation: ct);
    }
}

/// <summary>
/// FastEndpoints: This is a GET request endpoint
/// </summary>
/// Notice how this is an (Endpoint) : EndpointWithoutRequest as opposed to the endpoint above. 
/// Since there's no request, assume it's just asking for the OwnedStockDB List
public class GetStockEndpoint : EndpointWithoutRequest<List<Stock>>
{
    public override void Configure()
    {
        // This 
        Get("/api/owned-stocks");
        AllowAnonymous();
    }

    public override async Task HandleAsync(CancellationToken ct)
    {
        await SendAsync(OwnedStockDB.OwnedStockData, cancellation: ct);
    }
}

/// <summary>
/// FastEndpoints: This is a GET request endpoint
/// </summary>
/// Again, notice how this is an EndpointWithoutRequest
/// The endpoint (since it includes the companyName string in the url) will use that given company name to return the stock data
public class GetStockByCompanyNameEndpoint : EndpointWithoutRequest<Stock>
{
    public override void Configure()
    {
        Get("/api/owned-stocks/{companyName}");
        AllowAnonymous();
    }

    public override async Task HandleAsync(CancellationToken ct)
    {
        var companyNameFromRoute = Route<string>("companyName");
        var stock = OwnedStockDB.OwnedStockData.FirstOrDefault(x => x.companyName == companyNameFromRoute);

        if (stock is null)
        {
            await SendNotFoundAsync(cancellation: ct);
            return;
        }

        await SendAsync(stock, cancellation: ct);
    }
}

/// <summary>
/// FastEndpoints: This is a PUT request endpoint
/// </summary>
public class UpdateStockByCompanyNameEndpoint : Endpoint<Stock, Stock>
{
    public override void Configure()
    {
        // This 
        Put("/api/owned-stocks/");
        AllowAnonymous();
    }

    public override async Task HandleAsync(Stock req, CancellationToken ct)
    {
        int stockIndex = -1;

        for (int i = 0; i < OwnedStockDB.OwnedStockData.Count(); i++)
        {
            if (String.Equals(OwnedStockDB.OwnedStockData[i].companyName, req.companyName))
            {
                stockIndex = i;
                break;
            }
        }

        if(stockIndex == -1)
        {
            await SendNotFoundAsync(cancellation: ct);
            return;
        }

        OwnedStockDB.OwnedStockData[stockIndex] = req;

        await SendAsync(OwnedStockDB.OwnedStockData[stockIndex]);

        
    }
}


/// <summary>
/// FastEndpoints: This is a DELETE request endpoint
/// </summary>
public class DeleteStockByCompanyNameEndpoint : EndpointWithoutRequest<List<Stock>>
{
    public override void Configure()
    {
        // This 
        Delete("/api/owned-stocks/{companyName}");
        AllowAnonymous();
    }

    public override async Task HandleAsync(CancellationToken ct)
    {
        int stockIndex = -1;
        var companyNameFromRoute = Route<string>("companyName");

        for (int i = 0; i < OwnedStockDB.OwnedStockData.Count(); i++)
        {
            if (String.Equals(OwnedStockDB.OwnedStockData[i].companyName, companyNameFromRoute))
            {
                stockIndex = i;
                break;
            }
        }

        if (stockIndex == -1)
        {
            await SendNotFoundAsync(cancellation: ct);
            return;
        }

        OwnedStockDB.OwnedStockData.RemoveAt(stockIndex);

        await SendAsync(OwnedStockDB.OwnedStockData);


    }
}

#endregion
