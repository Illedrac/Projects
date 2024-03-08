using FastEndpoints;

public class JobQueueCommandHandler(ILogger<JobQueueCommand> logger) : ICommandHandler<JobQueueCommand>
{
    public async Task ExecuteAsync(JobQueueCommand command, CancellationToken ct)
    {
        await Task.Delay(1, ct);

        logger.LogInformation(" JobQueueCommand from id : {id} message {msg}", command.Id, command.message);

    }
}