using FastEndpoints;

/// <summary>
/// FastEndpoints: This is a POST request endpoint
/// Given a Stock DTO request, this will add that Stock to the DB (assuming it's not already in the DB)
/// Note: If the request Stock DTO is already in the DB, it is assumed (since this is a POST) that it shouldn't be updated. 
///       If it were meant to be updated, the UpdateStockByCompanyNameEndpoint should be used.
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
        if (OwnedStockDB.OwnedStockData.Find(q => q.companyName == req.companyName) == null)
        {
            OwnedStockDB.OwnedStockData.Add(req);
        }

        await SendAsync(OwnedStockDB.OwnedStockData, cancellation: ct);

    }
}

