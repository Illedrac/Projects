using FastEndpoints;

public class JobQueueCommand : ICommand
{
    public int Id { get; set; }
    public string message { get; init; } = default!;
}