using FastEndpoints;


/// <summary>
/// FastEndpoints : This is a simple DTO for JobRecords
/// </summary>
public sealed class JobRecord : IJobStorageRecord
{
    public string QueueID { get; set; } = default!;
    public object Command { get; set; } = default!;
    public DateTime ExecuteAfter { get; set; }
    public DateTime ExpireOn { get; set; }
    public bool IsComplete { get; set; }
}
