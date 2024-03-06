using FastEndpoints;

/// <summary>
/// FastEndpoints: This is a GET request endpoint
/// </summary>
/// Notice how this is an (Endpoint) : EndpointWithoutRequest as opposed to the endpoint above. 
/// Since there's no request, assume it's just asking for the OwnedStockDB List
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
