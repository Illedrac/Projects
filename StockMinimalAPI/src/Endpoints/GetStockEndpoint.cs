using FastEndpoints;

/// <summary>
/// FastEndpoints: This is a GET request endpoint
/// This allows you to get all owned stocks in the DB
/// </summary>
public class GetStockEndpoint : EndpointWithoutRequest<List<Stock>>
{
    public override void Configure()
    {
        Get("/api/owned-stocks");
        AllowAnonymous();
    }

    public override async Task HandleAsync(CancellationToken ct)
    {
        await SendAsync(OwnedStockDB.OwnedStockData, cancellation: ct);
    }
}
