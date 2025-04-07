namespace RSVPSystem.Models
{
    public class Attendee
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Email { get; set; }
        public string Phone { get; set; }
        public List<string> Parties { get; set; } // 存储用户参加的派对

        public Attendee()
        {
            Parties = new List<string>();
        }
    }
}