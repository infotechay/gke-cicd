variable "github_token" {
  description = "GitHub token for authentication"
  type        = string
  sensitive   = true
}

variable "github_owner" {
  description = "GitHub account or organization"
  type        = string
}

variable "target_repository" {
  description = "Target repository where secrets will be created"
  type        = string
}

variable "target_environment" {
  description = "Target environment where secrets will be added"
  type        = string
}
