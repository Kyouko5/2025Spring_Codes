using System.ComponentModel.DataAnnotations;

namespace RSVPSystem.Models
{
    public class Party
    {
        [Key]
        public int Id { get; set; }
        public string Name { get; set; } = string.Empty;
        public string Location { get; set; } = string.Empty;
        public DateTime Date { get; set; }

        // Navigation property for many-to-many relationship
        public ICollection<AttendeeParty> AttendeeParties { get; set; } = new List<AttendeeParty>();
    }
}