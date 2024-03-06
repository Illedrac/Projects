using FastEndpoints;

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