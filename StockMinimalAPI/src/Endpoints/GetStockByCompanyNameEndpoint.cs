using FastEndpoints;

/// <summary>
/// FastEndpoints: This is a GET request endpoint
/// Given the companyName in the url, this returns that Stock DTO matching on companyName (if it's in the DB)
/// </summary>
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