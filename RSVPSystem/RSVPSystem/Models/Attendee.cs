using System.ComponentModel.DataAnnotations;

namespace RSVPSystem.Models
{
    public class Attendee
    {
        [Key]
        public int Id { get; set; }
        public string Name { get; set; } = string.Empty;
        public string Email { get; set; } = string.Empty;
        public string Phone { get; set; } = string.Empty;
        
        // Navigation property for many-to-many relationship
        public ICollection<AttendeeParty> AttendeeParties { get; set; } = new List<AttendeeParty>();
    }
}