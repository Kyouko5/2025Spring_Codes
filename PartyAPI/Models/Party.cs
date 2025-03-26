// Models/Party.cs
namespace PartyAPI.Models
{
    public class Party
    {
        public int Id { get; set; }
        public string? Topic { get; set; }
        public string? Location { get; set; }
        public DateTime Time { get; set; }
    }
}