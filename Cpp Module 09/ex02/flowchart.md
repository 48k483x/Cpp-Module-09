``` mermaid 
flowchart TD
    A["1. [(10,3), (5,7), (7,6), (-1,4)]"] --> B["2. [(10,3), (5,7)]"]
    A --> C["6. [(7,6), (-1,4)]"]
    
    B --> D["3. [(10,3)]"]
    B --> E["4. [(5,7)]"]
    
    C --> F["7. [(7,6)]"]
    C --> G["8. [(-1,4)]"]
    
    D --> H["Returns [(10,3)]"]
    E --> I["Returns [(5,7)]"]
    
    H & I --> J["5. Merge: [(5,7), (10,3)]"]
    
    F --> K["Returns [(7,6)]"]
    G --> L["Returns [(-1,4)]"]
    
    K & L --> M["9. Merge: [(7,6), (-1,4)]"]
    
    J & M --> N["10. Final Merge: [(5,7), (7,6), (10,3), (-1,4)]"]

    style A fill:#f9f,stroke:#333,stroke-width:2px
    style N fill:#f9f,stroke:#333,stroke-width:2px
```