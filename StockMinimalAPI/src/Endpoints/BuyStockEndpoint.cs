using FastEndpoints;

/// <summary>
/// FastEndpoints: This is a POST request endpoint
/// This is an enpoint to create an event using a PublishAsync request that will be handled by the StockBoughtHandler
/// /// </summary>
public class BuyStockEndpoint : Endpoint<Stock>
{
    public override void Configure()
    {
        Post("/api/owned-stocks/buy");
        AllowAnonymous();
    }

    public override async Task HandleAsync(Stock req, CancellationToken ct)
    {
        await PublishAsync(req);

        await SendOkAsync(cancellation: ct);
    }
}