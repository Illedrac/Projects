using FastEndpoints;

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