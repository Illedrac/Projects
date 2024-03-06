using FastEndpoints;

/// <summary>
/// FastEndpoints: This is a POST request endpoint
/// </summary>
public class CreateStockEndpoint : Endpoint<Stock, List<Stock>>
{
    public override void Configure()
    {
        Post("/api/owned-stocks");
        AllowAnonymous();
    }

    public override async Task HandleAsync(Stock req, CancellationToken ct)
    {
        OwnedStockDB.OwnedStockData.Add(req);

        await SendAsync(OwnedStockDB.OwnedStockData, cancellation: ct);
    }
}

